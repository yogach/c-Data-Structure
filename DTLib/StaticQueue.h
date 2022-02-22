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
    T m_space[N];  //和StaticStack类似 当泛指类型为类类型时 创建本对象时会调用泛指类型的构造函数
    int m_front;   //队列头
    int m_rear;    //队列尾
    int m_length;

public:
    StaticQueue()  //O(1)
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity() const //O(1)
    {
        return N;
    }

    void add(const T& e) //O(1)
    {
        if( m_length < N )
        {
            m_space[m_rear] = e;
            m_rear = ( m_rear + 1 ) % N; //使用这种循环的方式 可以节约移动数据的时间
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue...");
        }
    }

    void remove()  //O(1)
    {
        if( m_length > 0 )
        {
            m_front = ( m_front + 1 ) % N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue...");
        }
    }

    T front() const  //O(1)
    {
        if( m_length > 0 )
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue...");
        }
    }

    void clear()  //O(1)
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int length() const  //O(1)
    {
        return m_length;
    }

};

}

#endif // STATICQUEUE_H
