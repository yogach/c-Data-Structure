#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template < typename T, int N >
class StaticStack : public Stack<T>
{
protected:
    T m_space[N]; //此处存在缺陷 当泛指类型T为类类型时，创建StaticStack时，会调用T的构造函数
    int m_top;
    int m_size;

public:
    StaticStack()  //O(1)
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const //O(1)
    {
        return N;
    }

    void push(const T &e) //O(1)
    {
        if( m_size < N )
        {
            m_space[m_top + 1] = e;
            m_size++;
            m_top++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack....");
        }
    }

    void pop()  //O(1)
    {
        if( m_size > 0 )
        {
            m_size--;
            m_top--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current stack....");
        }
    }

    T top() const  //O(1)
    {
        if( m_size > 0 )
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current stack....");
        }
    }

    void clear()  //O(1)
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const  //O(1)
    {
        return m_size;
    }

};

}

#endif // STATICSTACK_H
