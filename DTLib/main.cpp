#include <iostream>
#include "LinkStack.h"
#include "Queue.h"

using namespace std;
using namespace DTLib;

template < typename T >
class StackToQueue : public Queue<T>
{
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;

    void move() const
    {
        if( m_stack_out.size() == 0 )
        {
            while( m_stack_in.size() > 0)
            {
                m_stack_out.push( m_stack_in.top() );
                m_stack_in.pop();
            }
        }
    }

public:
    void add(const T& e)
    {
        m_stack_in.push(e);
    }

    void remove()
    {
        move();

        if( m_stack_out.size() != 0 )
        {
            m_stack_out.pop();
        }
        else
        {
            THROW_EXCEPTION(InvaildOperationException, "No element in current queue...");
        }

    }

    T front() const
    {
        move();

        if( m_stack_out.size() != 0 )
        {
            return m_stack_out.top();
        }
        else
        {
            THROW_EXCEPTION(InvaildOperationException, "No element in current queue...");
        }
    }

    void clear()
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }

    int length() const
    {
        return m_stack_in.size() + m_stack_out.size();
    }
};

int main()
{
    StackToQueue<int> sq;

    for(int i=0; i<20; i++)
    {
        sq.add(i);
    }

    while( sq.length() > 0)
    {
        cout << sq.front() << endl;

        sq.remove();
    }

    return 0;
}
