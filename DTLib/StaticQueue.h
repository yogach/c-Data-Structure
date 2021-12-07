#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace DTLib
{

template < typename T, int N >
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;   //队列头
    int m_rear;    //队列尾
    int m_length;

public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity() const
    {
        return N;
    }

    void add(const T& e)
    {
        if( m_length < N )
        {
            m_space[m_rear] = e;
            m_rear = ( m_rear + 1 ) % N; //使用这种循环的方式 可以节约移动数据的时间
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvaildOperationException, "No space in current queue...");
        }
    }

    void remove()
    {
        if( m_length > 0 )
        {
            m_front = ( m_front + 1 ) % N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvaildOperationException, "No space in current queue...");
        }
    }

    T front() const
    {
        if( m_length > 0 )
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvaildOperationException, "No space in current queue...");
        }
    }

    void clear()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int length() const
    {
        return m_length;
    }

};

}

#endif // STATICQUEUE_H
