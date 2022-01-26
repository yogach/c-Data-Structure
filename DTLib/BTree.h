#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"


namespace DTLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

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

    virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {
        bool ret = true;

        //按位置进行插入 如果对应位置上不为空 则插入失败
        if( pos == ANY )
        {
            if( np->left == NULL )
            {
                np->left = n;
            }
            else if( np->right == NULL )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == LEFT )
        {
            if( np->left == NULL )
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == RIGHT )
        {
            if( np->right == NULL )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }

public:
    bool insert(TreeNode<T>* node)
    {
        return insert(node, ANY);
    }

    virtual bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;

        if( node != NULL )
        {
            //如果根结点为空
            if( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                //在树中查找需要插入节点的父节点
                BTreeNode<T>* np = find(node->parent);

                if( np != NULL )
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvaildParamenterException, "Invaild parent tree node...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvaildParamenterException, "Parameter node can not be NULL...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;
        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if( node == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create BTreeNode..");
        }
        else
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            //如果插入失败 则需要释放之前申请的BTreeNode对象
            if( !ret )
            {
                delete node;
            }
        }


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
