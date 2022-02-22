#ifndef ARRAY_H
#define ARRAY_H

#include "Exception.h"
#include "Object.h"

namespace DTLib {

template <typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i, const T& e)
    {
        bool ret = ( (0 <= i) && (i < length()));

        if( ret )
        {
            m_array[i] = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e)
    {
        bool ret = ( (0 <= i) && (i < length()) );

        if( ret )
        {
            e = m_array[i];
        }

        return ret;

    }

    //数组操作访问符
    T& operator [](int i)
    {
        if( (0 <= i) && (i < length()) )
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
        }
    }

    T operator [](int i) const
    {
        //去除对象的只读属性后 直接调用数组操作符重载
        return (const_cast<Array<T>&>(*this))[i];
    }

    T* array() const
    {
        return m_array;
    }

    virtual int length() const = 0;

};

}


#endif // ARRAY_H
