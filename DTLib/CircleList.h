#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace DTLib
{

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    //此处的typename用于指示LinkList<T>::Node是类型不是函数
    typedef typename LinkList<T>::Node Node;

    //对传入的i值进行取余操作
    int mod(int i) const   // O(1)
    {
        return ( this->m_length == 0) ? 0 : (i % this->m_length);
    }

    Node* last() const  //O(n)
    {
        return this->position(this->m_length);
    }

    void last_to_first() const  //O(1)
    {
        last()->next = this->m_header.next;
    }

public:
    bool insert(const T& e)   //O(n)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e) // O(n) + O(n) => O(2n) => O(n)
    {
        bool ret = true;

        i = i % (this->m_length + 1); //对i取余数 防止i值过大

        ret = LinkList<T>::insert(i, e); //O(n)

        //当插入成功且插入的时头节点时 需要重新连接尾节点和头节点
        if( ret && (i == 0) )
        {
            last_to_first();     //O(n)
        }

        return ret;
    }

    bool remove(int i) // O(n)
    {
        bool ret = true;

        i = mod(i);

        //当需要移除的节点是首节点时，在链表长度大于0时，需要重新连接尾节点和首节点
        if( i == 0 )
        {
            Node* toDel = this->m_header.next;

            if( toDel != NULL )
            {
                this->m_header.next = toDel->next;
                this->m_length --;

                if( this->m_length > 0 )
                {
                    last_to_first();   //O(n)

                    if( this->m_current == toDel )
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                }

                this->destroy(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(mod(i));  //O(n)
        }


        return ret;
    }

    bool set(int i, const T& e) // O(n)
    {
        return LinkList<T>::set(mod(i), e);
    }

    T get(int i) const        // O(n)
    {
        return LinkList<T>::get(mod(i));
    }

    bool get(int i, const T& e) const  // O(n)
    {
        return LinkList<T>::get(mod(i), e);
    }

    int find(const T& e) const //O(n)
    {
        int ret = -1;
        Node* slider = this->m_header.next;

        //使用链表长度来作为链表结束的判断依据 而不是下一个节点为NULL
        for(int i=0; i<this->m_length; i++)
        {
            if( slider->value == e )
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void clear() // O(n)
    {
        while( this->m_length > 1) //O(n)
        {
            remove(1);   //每次移除1节点时，其时间实际是一个固定值
        }

        //当剩下最后一个节点时，特殊处理
        if( this->m_length == 1)
        {
            Node* toDel = this->m_header.next;

            this->m_header.next = NULL;
            this->m_length = 0;
            this->m_current = NULL;

            this->destroy(toDel);
        }
    }

    bool move(int i, int step) // O(n)
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end() //O(1)
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleList() // O(n)
    {
        clear();
    }
};

}

#endif // CIRCLELIST_H
