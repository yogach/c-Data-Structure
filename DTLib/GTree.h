#ifndef GTREE_H
#define GTREE_H

#include "GTreeNode.h"
#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"


namespace DTLib
{

template < typename T >
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;

    GTree(const GTree<T>&);
    GTree<T>& operator = (const GTree<T>&);

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

            if( node->flag() == true)
            {
              delete node;
            }

        }
        else //node == NULL
        {
            return;
        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if( ret == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree.");
        }
        else
        {
            //假设删除的是根节点
            if( root() == node )
            {
                this->m_root = NULL;
            }
            else
            {
                //找到需要删除节点的父节点
                GTreeNode<T>* parent = dynamic_cast<GTreeNode<T>*>(node->parent);

                //删除子节点
                parent->child.remove(parent->child.find(node));

                node->parent = NULL;
            }

            ret->m_root = node; //将需要删除的节点作为树返回
        }
    }

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1; //node不为空 则本身节点为1

            //遍历所有的子节点数量
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                //得到所有子节点的高度 找到其最高的高度
                int h = height(node->child.current());

                if( ret < h )
                {
                    ret = h;
                }
            }

            ret = ret + 1; //加上根结点的高度
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = node->child.length(); //得到本节点的子节点树（度数）

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                //得到各字节点的度数
                int d = degree(node->child.current());

                if( ret < d )
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

public:

    GTree()
    {

    }

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

        GTreeNode<T>* node = GTreeNode<T>::NewNode();

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
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value); //查找树中是否存在有该值的节点

        if( node == NULL )
        {
            THROW_EXCEPTION(InvaildParamenterException, "Can not find the node via parameter value..");
        }
        else
        {
            remove(node, ret);

            m_queue.clear();
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;

        node = find(node); //查找节点是否存在

        if( node == NULL )
        {
            THROW_EXCEPTION(InvaildParamenterException, "Can not find the node via parameter value..");
        }
        else
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);

            m_queue.clear();
        }

        return ret;
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
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());
        this->m_root = NULL;

        m_queue.clear();
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if( ret )
        {
            m_queue.clear(); //重新开始遍历后 清空队列
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if( ret )
        {
            GTreeNode<T>* node = m_queue.front(); //得到队列首元素

            m_queue.remove(); //移除该元素

            //将移除元素的子节点依次加入队列中
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        if( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvaildOperationException, "No value in current position..");
        }
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
