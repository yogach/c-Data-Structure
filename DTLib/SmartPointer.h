#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace DTLib {

template <typename T>
class SmartPointer : public Object
{
protected:
    T* m_pointer;

public:
    SmartPointer(T* p = NULL)
    {
        m_pointer = p;
    }

    //拷贝构造函数
    //得到对应的内存地址后 将赋值的对象设为NULL
    SmartPointer(const SmartPointer<T>& obj)
    {
        m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL; //使用const_cast取消对象的只读属性
    }

    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if( this != &obj ) //防止自赋值
        {
            delete m_pointer;

            m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }

        return *this;
    }

    T* operator ->()
    {
        return m_pointer;
    }

    T& operator *()
    {
        return *m_pointer;
    }

    bool isNULL()
    {
        return (m_pointer == NULL);
    }

    T* get()
    {
        return m_pointer;
    }

    ~SmartPointer()
    {
        delete m_pointer;
    }

};
}

#endif // SMARTPOINTER_H
