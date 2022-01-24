#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib {

template < typename T >
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator = (const TreeNode<T>&);


    void* operator new(long unsigned int size) throw()
    {
        return Object::operator new(size);
    }

public:
   T value;  //树节点中的值
   TreeNode<T>* parent; //树节点的父指针

   TreeNode()
   {
       m_flag = false;
       parent = NULL;
   }

   bool flag()
   {
       return m_flag;
   }

   virtual ~TreeNode();
};

template < typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
