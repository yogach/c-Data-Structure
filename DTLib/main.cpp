#include <iostream>
#include "GTree.h"
#include "BTree.h"

using namespace std;
using namespace DTLib;

int main()
{    
    BTree<int> bt;
    BTreeNode<int>* n;

    bt.insert(1, NULL);

    n = bt.find(1);
    bt.insert(2, n);
    bt.insert(3, n);

    n = bt.find(2);
    bt.insert(4, n);
    bt.insert(5, n);

    n = bt.find(4);
    bt.insert(8, n);
    bt.insert(9, n);

    n = bt.find(5);
    bt.insert(10, n, LEFT);

    n = bt.find(3);
    bt.insert(6, n);
    bt.insert(7, n);

    cout << bt.count() << endl;
    cout << bt.height() << endl;
    cout << bt.degree() << endl;

    cout << endl;

    BTree<int> nbt;

    nbt.insert(0, NULL);

    n = nbt.find(0);
    nbt.insert(6, n);
    nbt.insert(2, n);

    n = nbt.find(2);
    nbt.insert(7, n);
    nbt.insert(8, n);

    SharedPointer< BTree<int> > t = bt.add(nbt);

   /* SharedPointer< Array<int> > r = t->traversal(PreOrder);

    for(int i=0; i<r->length(); i++)
    {
        cout << (*r)[i] << " ";
    }*/

    for(t->begin(); !t->end(); t->next())
    {
        cout << t->current() << " " ;
    }


    return 0;
}
