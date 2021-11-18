#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include "Exception.h"
#include <cstdlib>

namespace DTLib {

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int *m_ref; //用于指示所指向空间的引用次数

    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if( this->m_ref )
        {
            (*this->m_ref) ++; //增加引用次数
        }
    }
public:
    SharedPointer(T* p=NULL ) : m_ref(NULL)
    {
        if( p )
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));

            if( this->m_ref )
            {
                (*this->m_ref) = 1; //设置所指空间的引用次数为1
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer object...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
    {
        assign(obj);
    }

    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if( this != &obj )
        {
            clear(); //首先清除当前对象指向的地址
            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        T* toDel = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = NULL;
        this->m_ref = NULL;

        if( ref )
        {
            (*ref)--;

            //当此堆空间没有SharedPointer指向后 释放两者的空间
            if( *ref == 0 )
            {
                free(ref);
                delete toDel;
            }
        }

    }

    ~SharedPointer()
    {
        clear();
    }

};

template <typename T>
bool operator ==(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template <typename T>
bool operator !=(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l == r); //此处继续调用上面定义的==重载
}

}

#endif // SHAREDPOINTER_H
