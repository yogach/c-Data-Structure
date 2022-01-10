#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib {

template < typename T >
class TreeNode : public Object
{
public:
   T value;
   TreeNode<T>* parent;

   TreeNode()
   {
       parent = NULL;
   }

   virtual ~TreeNode();
};

}

#endif // TREENODE_H
