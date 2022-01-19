#ifndef GTREENODE_H
#define GTREENODE_H

#include "Tree.h"
#include "LinkList.h"


namespace DTLib {

template < typename T >
class GTreeNode : public TreeNode<T>
{
protected:
    bool m_flag;

    GTreeNode(const GTreeNode<T>&);
    GTreeNode<T>& operator = (const GTreeNode<T>&);


    void* operator new(long unsigned int size) throw()
    {
        return Object::operator new(size);
    }

public:
    LinkList<GTreeNode<T>* > child; //当前节点的子节点

    GTreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if( ret != NULL )
        {
            ret->m_flag = true;
        }

        return ret;
    }
};

}

#endif // GTREENODE_H
