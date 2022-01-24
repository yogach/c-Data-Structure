#include <iostream>
#include "GTree.h"
#include "BTree.h"

using namespace std;
using namespace DTLib;

int main()
{    
    BTree<int> bt;
    BTreeNode<int> btn;

    bt.find(1);
    bt.find(&btn);

    return 0;
}
