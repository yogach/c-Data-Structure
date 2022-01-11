#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib {

template < typename T >
class TreeNode : public Object
{
public:
   T value;  //树节点中的值
   TreeNode<T>* parent; //树节点的父指针

   TreeNode()
   {
       parent = NULL;
   }

   virtual ~TreeNode();
};

template < typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
