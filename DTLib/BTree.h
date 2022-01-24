#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"


namespace DTLib
{

template < typename T >
class BTree : public Tree<T>
{
protected:
    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            //如果当前节点的值等于需要的值 直接返回
            if( node->value == value )
            {
                ret = node;
            }
            else
            {
                //如果返回值为空 则到左右子节点内进行递归查找
                if( ret == NULL )
                {
                    ret = find(node->left, value);
                }

                if( ret == NULL )
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if( node == obj )
        {
            ret = node;
        }
        else
        {
            if( node != NULL )
            {
                //如果返回值为空 则到左右子节点内进行递归查找
                if( ret == NULL )
                {
                    ret = find(node->left, obj);
                }

                if( ret == NULL )
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }
public:
    bool insert(TreeNode<T>* node)
    {
        int ret = true;

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        int ret = true;

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        return NULL;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return NULL;
    }

    int count() const
    {
        return NULL;
    }

    int height() const
    {
        return NULL;
    }

    void clear()
    {
        this->m_root = NULL;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
