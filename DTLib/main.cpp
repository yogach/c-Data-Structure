#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace DTLib;


int main()
{
    ListGraph<char, int> g(4);

    g.setVertex(0, 'A');
    g.setVertex(1, 'B');
    g.setVertex(2, 'C');
    g.setVertex(3, 'D');

    for(int i=0; i<g.vCount(); i++)
    {
        cout << i << " : " << g.getVertex(i) << endl;
    }

    g.setEdge(0, 1, 5);
    g.setEdge(0, 3, 5);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    cout << "W(0, 1): " << g.getEdge(0, 1) << endl;
    cout << "W(0, 3): " << g.getEdge(0, 3) << endl;
    cout << "W(1, 2): " << g.getEdge(1, 2) << endl;
    cout << "W(2, 3): " << g.getEdge(2, 3) << endl;
    cout << "W(3, 1): " << g.getEdge(3, 1) << endl;

    cout << "eCount: " << g.eCount() << endl;

    SharedPointer< Array<int> > aj = g.getAdjacent(0);

    for(int i=0; i<aj->length(); i++)
    {
        cout << (*aj)[i] << " ";
    }

    cout << endl;

    cout << "ID(1): " << g.ID(1) << endl;
    cout << "OD(1): " << g.OD(1) << endl;
    cout << "TD(1): " << g.TD(1) << endl;

    g.removeVertex(); //删除最后一个节点

    cout << "eCount: " << g.eCount() << endl;

    cout << "W(0, 1): " << g.getEdge(0, 1) << endl;
    cout << "W(1, 2): " << g.getEdge(1, 2) << endl;
    cout << "W(2, 3): " << g.getEdge(2, 3) << endl;

    /*

    cout << "vCount: " << g.vCount() << endl;





    cout << endl;

    cout << "Delete Edge: " << endl;



    cout << "eCount: " << g.eCount() << endl;

    g.setVertex(0, 100);

    cout << "V(0): " << g.getVertex(0) << endl;

    //cout << "W(0, 1)" << g.getEdge(0, 1) << endl;*/

    return 0;
}
