#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib {

template < typename T >
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    //mutable 用于移除只读属性
    //这里使用了一个与Node节点内存结构相同的节点来作为头节点 是为了防止创建头节点时，可能会调用泛指类型T的构造函数
    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
    }m_header;
    int m_length;

    Node* position(int i) const   //O(n)
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }
public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
    }

    bool insert(const T& e)    //O(n)
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T& e) //O(n)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {
            Node* node = new Node();

            if( node != NULL )
            {
                Node* current = position(i);

                node->value = e;
                node->next = current->next;
                current->next = node;

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert element...");
            }
        }

        return ret;
    }

    bool remove(int i)     //O(n)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {
            Node* current = position(i);

            Node* toDel = current->next;

            current->next = toDel->next;

            delete toDel;

            m_length --;
        }

        return ret;
    }

    bool set(int i, const T& e)  //O(n)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {
            Node* current = position(i);

            current->next->value = e;
        }

        return ret;
    }

    int find(const T& e) const  //O(n)
    {
        int ret = -1;
        int i = 0;
        Node* node = m_header.next;

        while (node) {
            if(node->value == e)
            {
               ret = i;
               break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }

        return ret;
    }

    T get(int i) const   //O(n)
    {
        T ret = 0;

        if( (0 <= i) && (i <= m_length) )
        {
            Node* current = position(i);

            ret = current->next->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Value i is invaild...");
        }

        return ret;
    }

    bool get(int i, T& e) const  //O(n)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {
            Node* current = position(i);

            e = current->next->value;
        }

        return ret;
    }

    int length() const    //O(1)
    {
        return m_length;
    }

    void clear()    //O(n)
    {
        while ( m_header.next ) {
            Node* toDel = m_header.next;

            m_header.next = toDel->next;

            delete toDel;
        }
    }

    ~LinkList()      //O(n)
    {
        clear();
    }
};

}

#endif // LINKLIST_H
