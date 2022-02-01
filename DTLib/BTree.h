#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DTLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
};

template < typename T >
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;
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

    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if( ret == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree...");
        }
        else
        {
            //如果需要删除的根节点 直接删除
            if( root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if( parent->left == node )
                {
                    parent->left = NULL;
                }
                else if( parent->right == node)
                {
                    parent->right = NULL;
                }

                node->parent = NULL;

            }

            //将删除节点作为树返回
            ret->m_root = node;
        }
    }

    virtual void free(BTreeNode<T>* node)
    {
        //如果node不为空 递归释放
        if( node != NULL )
        {
            free(node->left);
            free(node->right);

            if( node->flag() )
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = count(node->left) + count(node->right) + 1;
        }

        return ret;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            //递归的得到左边子树和右边子树的高度
            int lh = height(node->left);
            int lr = height(node->right);

            //得到两个子树中的最大高度 加上当前节点
            ret = ((lr > lh) ? lr : lh) + 1;
        }

        return ret;
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            BTreeNode<T>* child[] = {node->left, node->right};

            //假设node->left为非0 第一个!将其转化为0 第二个!将其转化为1
            //这样就可以判断左节点和右节点是否存在
            ret = ( !!node->left + !!node->right );

            //只有在度数小于2时才进行循环 因为二叉树的性质得到最大节点只能为2
            for(int i=0; (i<2) && (ret<2); i++)
            {
                int d = degree(child[i]);

                if( ret < d )
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

    //先序遍历
    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if( node != NULL )
        {
            //先访问节点的值 之后遍历左子树 再之后遍历右子树
            queue.add(node);
            preOrderTraversal(node->left, queue);
            preOrderTraversal(node->right, queue);
        }
    }

    //中序遍历
    void InOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if( node != NULL )
        {
            //先遍历左子树 之后访问节点的值 再之后遍历右子树
            InOrderTraversal(node->left, queue);
            queue.add(node);
            InOrderTraversal(node->right, queue);
        }
    }

    //后序遍历
    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if( node != NULL )
        {
            //先遍历左子树 再之后遍历右子树 最后访问节点的值
            postOrderTraversal(node->left, queue);
            postOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if( ret != NULL )
        {
            //首先分配一个树节点 作为根节点
            ret = BTreeNode<T>::NewNode();

            if( ret != NULL )
            {
                ret->value = node->value; //赋值

                //递归的方式clone左子树和右子树
                ret->left = clone(node->left);
                ret->right = clone(node->right);

                //处理子节点的父子关系
                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }

                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node...");
            }
        }
    }

    bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        if( lh == rh ) //如果两者地址相等 直接返回true
        {
            return true;
        }
        else if( (lh != NULL) && (rh != NULL ) )
        {
            //判断节点值是否相等 递归的判断左子树和右子树是否相等
            return (lh->value == rh->value) && equal(lh->left, rh->left) && equal(lh->right, rh->right);
        }
        else //else内的情况 则是lh 或 rh的其中一个为NULL的情况
        {
            return false;
        }
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
        BTree<T>* ret = NULL;
        BTreeNode<T>* node = find(value);

        if( node == NULL )
        {
            THROW_EXCEPTION(InvaildParamenterException, "Can not find the tree node via value...");
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
        BTree<T>* ret = NULL;

        //对需要删除的节点进行查找
        node = find(node);

        //如果可以找到则进行删除操作
        if( node == NULL )
        {
            THROW_EXCEPTION(InvaildParamenterException, "parameter node is invaild...");
        }
        else
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);
            m_queue.clear();
        }

        return ret;
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

        m_queue.clear();

        this->m_root = NULL;
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
            BTreeNode<T>* node = m_queue.front(); //得到队列首元素

            m_queue.remove(); //移除该元素

            if( node->left != NULL )
            {
                m_queue.add(node->left);
            }

            if( node->right != NULL )
            {
                m_queue.add(node->right);
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

    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        switch(order)
        {
        case PreOrder:
            preOrderTraversal(root(), queue);
            break;
        case InOrder:
            InOrderTraversal(root(), queue);
            break;
        case PostOrder:
            postOrderTraversal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvaildParamenterException, "Parameter order is invaild...");
            break;
        }

        ret = new DynamicArray<T>(queue.length()); //动态数组长度设置为queue的长度

        if( ret != NULL )
        {
            //将queue的数据依次写入ret array内
            for(int i=0; i<ret->length(); i++, queue.remove())
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create return array...");
        }

        return ret;
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree();

        if( ret != NULL )
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree...");
        }

        return ret;
    }

    //如果不使用引用调用 则会触发拷贝构造
    bool operator == (const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }

    bool operator != (const BTree<T>& btree)
    {
        return !((*this) == btree);
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
