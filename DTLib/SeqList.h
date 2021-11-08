#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

using namespace DTLib;

namespace DTLib {

template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;
    int m_length;

public:
    bool insert(const T& e)
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        ret = ret && ( (m_length) < capacity() ); //检查容量是否符合要求

        if( ret )
        {
            //将数组内容从后往前拷贝 留出一个位置给要插入的元素
            for(int p=m_length-1; p>=i; p--)
            {
                m_array[p+1] = m_array[p];
            }

            m_array[i] = e;
            m_length++;
        }

        return ret;
    }

    bool remove(int i )
    {
        bool ret = ( (0 <= i) && (i<m_length) );

        if( ret )
        {
            for(int p=i; p<(m_length-1); p++)
            {
                m_array[p] = m_array[p+1];
            }

            m_length -- ;
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ( (0 <= i) && (i<m_length) );

        if(ret)
        {
            m_array[i] = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = ( (0 <= i) && (i<m_length) );

        if( ret )
        {
           e = m_array[i];
        }

        return ret;
    }

    int length() const
    {
       return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    //顺序存储线性表的数组访问方式
    T& operator [](int i)
    {
        if( ( (0 <= i) && (i<m_length) ) )
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invaild... ");
        }
    }

    T operator [](int i) const
    {
        //使用const_cast去除对象的只读属性，之后直接调用重载的[]操作符
        return (const_cast<SeqList<T>&>(*this))[i];
    }

    //顺序存储空间的容量
    virtual int capacity() const = 0;
};


}


#endif // SEQLIST_H
