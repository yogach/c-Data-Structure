#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    //创建一个新空间 并将数据拷贝到新空间内
    T* copy(T* array, int length, int newLen)
    {
        T* ret = new T[newLen];

        if( ret != NULL )
        {
            int size = (length < newLen) ? length : newLen;

            for(int i=0; i<size; i++)
            {
               ret[i] = array[i];
            }
        }

        return ret;
    }

    //更新本对象内的m_array和m_length
    void update(T* array, int length)
    {
        if( array != NULL )
        {
            T* temp = this->m_array;

            this->m_array = array;
            this->m_length = length;

            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray object..");
        }
    }

    //将一块空间设置到m_array中
    void init(T* array, int length)
    {
        if( array != NULL )
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object..");
        }
    }

public:
    DynamicArray(int length)
    {
        init(new T[length], length);
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        init(copy(obj.m_array, obj.length(), obj.length()), obj.length());
    }

    DynamicArray<T>& operator = (const DynamicArray<T>& obj)
    {
        if( this != &obj ) //判断对象地址 避免自赋值
        {
            update(copy(obj.m_array, obj.length(), obj.length()), obj.length());
        }

        return *this;
    }

    int length() const
    {
        return m_length;
    }

    void resize(int length)
    {
        if( length != m_length )
        {
            update(copy(this->m_array, m_length, length), length);
        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};


}

#endif // DYNAMICARRAY_H
