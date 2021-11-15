#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib {

template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node; //将Node指定成父类中的struct Node对象

    //重载Node的new操作符
    struct SNode : public Node
    {
        void* operator new(long unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }

    };
    unsigned char m_space[sizeof(SNode) * N]; //固定长度空间 用于分配节点
    int m_used[N];

    Node* create()
    {
        SNode* ret = NULL;

        for(int i=0; i<N; i++)
        {
            //找到未使用的空间
            if( !m_used[i] )
            {
                ret = reinterpret_cast<SNode*>(m_space) + i; //指针运算得到对应地址
                ret = new(ret)SNode(); // 这种写法挺奇怪的
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void destroy(Node* pn)
    {
         SNode* space = reinterpret_cast<SNode*>(m_space);
         SNode* psn = dynamic_cast<SNode*>(pn);

         for(int i=0; i<N; i++)
         {
             //指针运算后找到对应空间
             if( psn == (space + i) )
             {
                 m_used[i] = 0;
                 psn->~SNode(); //虽然我们并没有实际定义~SNode 但其析构函数时默认创建的
             }
         }
    }

public:
    StaticLinkList()
    {
        for(int i=0; i<N; i++)
        {
            m_used[i] =0;
        }
    }

    int capacity()
    {
        return N;
    }
};

}

#endif // STATICLINKLIST_H
