#include <iostream>
#include "MatrixGraph.h"

using namespace std;
using namespace DTLib;

template < typename V, typename E>
void DFS(Graph<V, E>& g, int v, Array<bool>& visited)
{
    if( (0 <= v) && (v < g.vCount()) )
    {
        cout << v << endl; //访问顶点

        SharedPointer< Array<int>> aj = g.getAdjacent(v);

        visited[v] = true;

        for(int j=0; j<aj->length(); j++)
        {
            //判断顶点是否被访问过
            if( !visited[(*aj)[j]] )
            {
                DFS(g, (*aj)[j], visited); //执行遍历
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParamenterException, "Index i is invalid...");
    }
}

template < typename V, typename E>
void DFS(Graph<V, E>& g, int v)
{
    DynamicArray<bool> visited(g.vCount());

    for(int i=0; i<visited.length(); i++)
    {
        visited[i] = false;
    }

    DFS(g, v, visited);
}

int main()
{
    MatrixGraph<9, char, int> g;
    const char VD[] = "ABEDCGFHI";

    for(int i=0; i<9; i++)
    {
        g.setVertex(i, VD[i]);
    }

    g.setEdge(0, 1, 0);
    g.setEdge(1, 0, 0);

    g.setEdge(0, 3, 0);
    g.setEdge(3, 0, 0);

    g.setEdge(0, 4, 0);
    g.setEdge(4, 0, 0);

    g.setEdge(1, 2, 0);
    g.setEdge(2, 1, 0);

    g.setEdge(1, 4, 0);
    g.setEdge(4, 1, 0);

    g.setEdge(2, 5, 0);
    g.setEdge(5, 2, 0);

    g.setEdge(3, 6, 0);
    g.setEdge(6, 3, 0);

    g.setEdge(4, 6, 0);
    g.setEdge(6, 4, 0);

    g.setEdge(6, 7, 0);
    g.setEdge(7, 6, 0);

    g.setEdge(7, 8, 0);
    g.setEdge(8, 7, 0);

    SharedPointer< Array<int> > sa = g.DFS(0);

    for(int i=0; i<sa->length(); i++)
    {
        cout << (*sa)[i] << " ";
    }

    cout << endl;

    DFS(g, 0);

    return 0;
}
