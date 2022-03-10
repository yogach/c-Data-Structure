#include <iostream>
#include "MatrixGraph.h"
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

int search_max_path(Graph<int, int>& g, int v, Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
{
    int ret = 0;
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

        //找到最长路径
        if( ret < num )
        {
            ret = num;
        }
    }

    for(int i=0; i<aj->length(); i++)
    {
        if( ret == count[(*aj)[i]] )
        {
            path[v]->insert((*aj)[i]); //将所有和最长路径相等的顶点号加入到path内
        }
    }

    ret++; //将顶点本身加上

    count[v] = ret; //保存最长序列长度
    mark[v] = true; //标记v位置顶点 已找到最长序列

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

void init_array(Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
{
    for(int i=0; i<count.length(); i++)
    {
        count[i] = 0;
    }

    for(int i=0; i<path.length(); i++)
    {
        path[i] = new LinkList<int>();
    }

    for(int i=0; i<mark.length(); i++)
    {
        mark[i] = false;
    }
}

void print_path(Graph<int, int>& g, int v, Array< LinkList<int>* >& path, LinkList<int>& cp)
{
    cp.insert(v);

    //递归的终止条件是路径上没有后续顶点
    if( path[v]->length() > 0)
    {
       for(path[v]->move(0); !path[v]->end(); path[v]->next())
       {
           print_path(g, path[v]->current(), path, cp);
       }
    }
    else
    {
        //将cp内的顶点全部打印出来
       cout << "Element: ";

       for(cp.move(0); !cp.end(); cp.next())
       {
           cout << g.getVertex(cp.current()) << " ";
       }

       cout << endl;
    }

    cp.remove(cp.length() - 1); //去除最后一个顶点就相当于回溯
}

void print_max_path(Graph<int, int>& g, Array<int>& count, Array< LinkList<int>* >& path)
{
    int max = 0;
    LinkList<int> cp;

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
            print_path(g, i, path, cp);
        }
    }
}

void search_max_path(Graph<int, int> &g, Array<int> &count, Array< LinkList<int>* > &path, Array<bool> &mark)
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
    DynamicArray< LinkList<int>* > path(len);
    DynamicArray<bool> mark(len);
    SharedPointer< Graph<int, int> > g;

    g = create_graph(a, len);

    init_array(count, path, mark);

    search_max_path(*g, count, path, mark);

    print_max_path(*g, count, path);
}

int main()
{
    int a[] = {1, 3, 5, 4};
    solution(a, sizeof(a)/sizeof(a[0]));
    return 0;
}

