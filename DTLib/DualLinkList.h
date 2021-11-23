#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

namespace DTLib {

template < typename T >
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    //mutable 用于移除只读属性
    //这里使用了一个与Node节点内存结构相同的节点来作为头节点 是为了防止创建头节点时，可能会调用泛指类型T的构造函数
    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;
    }m_header;
    int m_length;
    Node* m_current;
    int m_step;

    Node* position(int i) const   //O(n)
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    //声明成virtual 则具备了多态属性
    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    DualLinkList()
    {
        m_header.next = NULL;
        m_header.pre = NULL;
        m_length = 0;
        m_current = NULL;
        m_step = 1;
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
            Node* node = create();

            if( node != NULL )
            {
                Node* current = position(i);
                Node* next = current->next;

                node->value = e;
                node->next = next;
                current->next = node;

                //假设插入的是0位置的节点
                if( current == reinterpret_cast<Node*>(&m_header) )
                {
                    node->pre = NULL;
                }
                else
                {
                    node->pre = current;
                }

                if( next != NULL )
                {
                    next->pre = node;
                }

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
            Node* next = toDel->next;

            if( m_current == toDel )
            {
                m_current = next;
            }

            current->next = next;

            if( next != NULL )
            {
                next->pre = current;
            }

            m_length --;

            destroy(toDel);
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

        while (node)
        {
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
        //在保持时间复杂度不变的情况下 修改为以下形式
        //对比LinkList的clear，此处需要修改的原因是，避免destroy时抛出异常导致
        //双向链表的连接状态出现改变
        while( m_length > 0)
        {
            remove(0);
        }
    }

    virtual bool move(int i, int step = 1)
    {
        bool ret = (0 <= i) && (i < m_length) && (step > 0);

        if( ret )
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    virtual bool end()
    {
        return (m_current == NULL);
    }

    virtual T current()
    {
        if( !end() )
        {
          return (m_current->value);
        }
        else
        {
            THROW_EXCEPTION(InvaildOperationException, "No Value in current position...");
        }
    }

    //m_current指向下一个节点
    virtual bool next()
    {
        int i = 0;

        while( (i < m_step) && (!end()) )
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    bool pre()
    {
        int i = 0;

        while( (i < m_step) && (!end()) )
        {
            m_current = m_current->pre;
            i++;
        }

        return (i == m_step);
    }

    ~LinkList()      //O(n)
    {
        clear();
    }
};

}

#endif // DUALLINKLIST_H
