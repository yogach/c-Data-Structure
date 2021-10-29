#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib {

template < typename T >
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;

public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];

        if( this->m_array != NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Enough to create Dynamic object...");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    //重新设置顺序存储空间大小
    void resize(int capacity)
    {
        //只有当重设大小和当前大小不同时，才进行重设
        if( capacity != m_capacity )
        {
            T* array = new T[capacity];

            if( array != NULL)
            {
                //对比当前大小和重设之后的大小 决定保留的元素项
                int length = (this->m_length < capacity  ? this->m_length : capacity );

                for(int i=0; i<length; i++)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;

                this->m_array = array;
                this->m_capacity = capacity;
                this->m_length = length;

                delete[] temp; //将这个放在最后执行 是为了防止delete时 出现异常
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory resize Dynamic object...");
            }

        }

    }

    ~DynamicList()
    {
        delete[] this->m_array;
    }

};

}

#endif // DYNAMICLIST_H
