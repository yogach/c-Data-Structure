#ifndef GTREE_H
#define GTREE_H

#include "GTreeNode.h"
#include "Tree.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class GTree : public Tree<T>
{
    //使用值来进行查找
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            //使用递归方式进行查找 终止条件即为找到对应节点
            if( node->value == value )
            {
                return node;
            }
            else
            {
                //使用递归的方式对当前节点的所有子节点进行查找
                //ret != NULL的时候会跳出循环 实际上就是找到第一个符合的即退出
                for(node->child.move(0); !node->child.end() && ( ret == NULL ); node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if( node == obj )
        {
            return node;
        }
        else
        {
            if( node != NULL )
            {
                //使用递归的方式对当前节点的所有子节点进行查找
                for(node->child.move(0); !node->child.end() && ( ret == NULL ); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

    void free(GTreeNode<T>* node)
    {
        if( node != NULL )
        {
            //使用递归的方式释放所有节点， 释放所有子节点后，再释放根节点
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }

            delete node;
        }
        else //node == NULL
        {
            return;
        }
    }

public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if( node != NULL )
        {
            //假设根节点为空
            if( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                //查找需要插入节点的父节点
                GTreeNode<T>* np = find(node->parent);

                if( np != NULL )
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                    //在当前节点的子节点中查找需要插入的节点是否已存在
                    //个人观点这里应该还是需要查找整颗树
                    //测试后也符合预期
                    if( np->child.find(n) < 0 )
                    {
                        np->child.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvaildOperationException, "invaild parent tree node..");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvaildParamenterException, "Parameter node is NULL..");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;

        GTreeNode<T>* node = new GTreeNode<T>();

        if( node != NULL )
        {
            node->parent = parent;
            node->value = value;

            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create GTreeNode");
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

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return 0;
    }

    int count() const
    {
        return 0;
    }

    int height() const
    {
        return 0;
    }

    void clear()
    {
        free(root());
        this->m_root = NULL;
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
