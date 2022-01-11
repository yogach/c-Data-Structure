#ifndef GTREENODE_H
#define GTREENODE_H

#include "Tree.h"
#include "LinkList.h"

namespace DTLib {

template < typename T >
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>* > child; //当前节点的子节点
};

}

#endif // GTREENODE_H
