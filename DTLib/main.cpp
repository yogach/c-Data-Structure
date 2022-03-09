#include <iostream>
#include "MatrixGraph.h"
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

int search_max_path(Graph<int, int>& g, int v, Array<int>& count, Array<int>& path, Array<bool>& mark)
{
    int ret = 0;
    int k = -1;
    SharedPointer< Array<int> > aj = g.getAdjacent(v); //得到v的邻接顶点数组

    //结束递归的条件是找不到邻接顶点
    //如果有依次查找邻接顶点的最长路径
    for(int i=0; i<aj->length(); i++)
    {
        int num = 0;

        if( !mark[(*aj)[i]] ) //只查找没有标记的顶点
        {
            //递归查找邻接顶点的最长路径
            num = search_max_path(g, (*aj)[i], count, path, mark);
        }
        else
        {
            num = count[(*aj)[i]];
        }

        if( ret < num )
        {
            ret = num;
            k = (*aj)[i];
        }
    }

    ret++; //将顶点本身加上

    count[v] = ret; //保存最长序列长度
    mark[v] = true; //标记v位置顶点 已找到最长序列
    path[v] = k; //k表示最长序列经过的第一个顶点

    return ret;
}

//将数组转化为有向图
SharedPointer< Graph<int, int> > create_graph(int* a, int len)
{
    ListGraph<int, int>* ret = new ListGraph<int, int>(len);

    for(int i=0; i<len; i++)
    {
        ret->setVertex(i, a[i]);
    }

    //根据最长不下降序列的概念 只将当前位置上的顶点和之后的其余顶点作比较 符合要求的就生成一条有向边
    for(int i=0; i<len; i++)
    {
        for(int j=i+1; j<len; j++)
        {
            if( a[i] <= a[j] )
            {
                ret->setEdge(i, j, 1);
            }
        }
    }

    return ret;
}

void init_array(Array<int>& count, Array<int>& path, Array<bool>& mark)
{
    for(int i=0; i<count.length(); i++)
    {
        count[i] = 0;
    }

    for(int i=0; i<path.length(); i++)
    {
        path[i] = -1;
    }

    for(int i=0; i<mark.length(); i++)
    {
        mark[i] = false;
    }
}

void print_max_path(Graph<int, int>& g, Array<int>& count, Array<int>& path)
{
    int max = 0;

    //得到所有顶点中最长的那个不下降序列
    for(int i=0; i<count.length(); i++)
    {
        if( max < count[i] )
        {
            max = count[i];
        }
    }

    cout << "Len: " << max << endl;

    for(int i=0; i<count.length(); i++)
    {
        if( max == count[i] )
        {
            cout << "Element: " << g.getVertex(i) << " ";

            //通过path数组 得到最长不下降序列经过的顶点
            for(int j=path[i]; j!=-1; j=path[j])
            {
                cout << g.getVertex(j) << " ";
            }

            cout << endl;
        }
    }
}

void search_max_path(Graph<int, int> &g, Array<int> &count, Array<int> &path, Array<bool> &mark)
{
    for(int i=0; i<g.vCount(); i++)
    {
        if( !mark[i] )
        {
            search_max_path(g, i, count, path, mark);
        }
    }
}

void solution(int* a, int len)
{
    DynamicArray<int> count(len);
    DynamicArray<int> path(len);
    DynamicArray<bool> mark(len);
    SharedPointer< Graph<int, int> > g;

    g = create_graph(a, len);

    init_array(count, path, mark);

    search_max_path(*g, count, path, mark);

    print_max_path(*g, count, path);
}

int main()
{
    int a[] = {3, 18, 7, 14, 10, 12, 23, 41, 16, 24};
    solution(a, sizeof(a)/sizeof(a[0]));
    return 0;
}

