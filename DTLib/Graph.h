#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Exception.h"
#include "Sort.h"

namespace DTLib {

template < typename E >
struct Edge : public Object
{
    int b; //起点
    int e; //终点
    E data;

    Edge(int i=-1, int j=-1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator ==(const Edge<E>& obj)
    {
        return ( (b == obj.b) && (e == obj.e) );
    }

    bool operator !=(const Edge<E>& obj)
    {
        return !(*this == obj);
    }

    bool operator < (const Edge<E>& obj)
    {
        return (data < obj.data);
    }

    bool operator > (const Edge<E>& obj)
    {
        return (data > obj.data);
    }
};

template < typename V, typename E>
class Graph : public Object
{
protected:
    template< typename T >
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

        if( ret != NULL )
        {
            //将队列按顺序添加到数组内
            for(int i=0; i<ret->length(); i++, queue.remove())
            {
                ret->set(i, queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create ret array...");
        }

        return ret;
    }

    //返回所有的edge
    SharedPointer< Array< Edge<E> > > getUndirectedEdge()
    {
        DynamicArray< Edge<E> >* ret = NULL;

        if( asUndirected() )
        {
            LinkQueue< Edge<E> > queue;

            for(int i=0; i<vCount(); i++)
            {
                for(int j=i; j<vCount(); j++)
                {
                    if( isAdjacent(i, j) ) //判断是否为邻接顶点
                    {
                        queue.add(Edge<E>(i, j, getEdge(i, j))); //写入队列
                    }
                }
            }

            ret = toArray(queue);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "This function for undirected graph only...");
        }

        return ret;
    }

    int find(Array<int>& p, int v)
    {
        //循环查找 直到找到 前驱标记数组内值为-1的顶点
        while( p[v] != -1 )
        {
            v = p[v];
        }

        return v;
    }
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;
    virtual bool isAdjacent(int i, int j) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    //判断是否为无相图
    bool asUndirected()
    {
        bool ret = true;

        for(int i=0; i<vCount(); i++)
        {
            for(int j=0; j<vCount(); j++)
            {
                //如果i到j有边为邻接节点
                if( isAdjacent(i, j) )
                {
                    //判断j到i是否有边 且两者的边的值是否相等
                    ret = ret && isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }

        return ret;
    }

    SharedPointer< Array< Edge<E> > > kruskal(const bool MININUN = true)
    {
        LinkQueue< Edge<E> > ret;
        SharedPointer< Array< Edge<E> > > edges = getUndirectedEdge();
        DynamicArray<int> p(vCount());

        //初始化前驱标记数组
        for(int i=0; i<p.length(); i++)
        {
            p[i] = -1;
        }

        Sort::Shell(*edges, MININUN); //对数组进行排序

        //当边数组结束 或者 返回数组长度等于图的总的边-1时 结束整个循环
        for(int i=0; (i<edges->length()) && (ret.length() < (vCount() - 1)); i++)
        {
            int b = find(p, (*edges)[i].b);
            int e = find(p, (*edges)[i].e);

            if( b != e)
            {
                p[e] = b;
                ret.add((*edges)[i]);
            }
        }

        if( ret.length() != (vCount() - 1) )
        {
           THROW_EXCEPTION(InvalidOperationException, "No enough edges for kruskal operator...");
        }

        return toArray(ret);
    }

    SharedPointer< Array< Edge<E> > > prim(const E& LIMIT, bool MININUM = true)
    {
        LinkQueue< Edge<E> > ret;

        //判断是否为无向图
        if( asUndirected() )
        {
            DynamicArray<int> adjVex(vCount()); //用于保存各顶点的邻接顶点
            DynamicArray<bool> mark(vCount()); //用于标记端点在T集合还是F集合
            DynamicArray<E> cost(vCount()); //用于保存各端点的边的权值
            SharedPointer< Array<int> > aj = NULL;
            bool end = false;
            int v = 0; //开始顶点编号

            for(int i=0; i<vCount(); i++)
            {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT;
            }

            mark[v] = true; //标记v顶点 在T集合

            aj = getAdjacent(v); //得到v顶点的邻接顶点

            //更新v节点的邻接顶点和边的权值
            for(int i=0; i<aj->length(); i++)
            {
                cost[(*aj)[i]] = getEdge(v, (*aj)[i]);
                adjVex[(*aj)[i]] = v;
            }

            for(int i=0; (i<vCount()) && !end; i++)
            {
                E m = LIMIT;
                int k = -1;

                for(int j=0; j<vCount(); j++)
                {
                    if( !mark[j] && (MININUM ? (cost[j] < m) : (cost[j] > m) ) )
                    {
                        m = cost[j]; //得到权值最小的
                        k = j; //得到与最小权值对应的顶点
                    }
                }

                end = (k == -1); //判断是否还有邻接顶点

                if( !end )
                {
                    ret.add( Edge<E>(adjVex[k], k, getEdge(adjVex[k], k) ) );

                    mark[k] = true;

                    aj = getAdjacent(k);

                    for(int j=0; j<aj->length(); j++)
                    {
                        //更新k顶点相关的cost和adjvex
                        //只更新F集合的顶点 以及 权值小的
                        if( !mark[(*aj)[j]] && (MININUM ? (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]) : (getEdge(k, (*aj)[j]) > cost[(*aj)[j]])) )
                        {
                            cost[(*aj)[j]] = getEdge(k, (*aj)[j]);
                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Prim operator is for undirected graph only...");
        }

        if( ret.length() != (vCount() - 1) )
        {
            THROW_EXCEPTION(InvalidOperationException, "No enough edge for prim....");
        }

        return toArray(ret);
    }

    SharedPointer< Array<int> > BFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if( (0 <= i) && (i < vCount()) )
        {
            LinkQueue<int> q; //保存正在遍历的元素
            LinkQueue<int> r; //保存已遍历元素
            DynamicArray<int> visited(vCount());

            //初始化visited数组
            for(int j=0; j<visited.length(); j++)
            {
                visited[j] = false;
            }

            q.add(i); //将遍历的头元素加入队列

            while( q.length() > 0 )
            {
                //得到队列首元素
                int v = q.front();
                q.remove();

                //判断是否访问过
                if( !visited[v] )
                {
                    SharedPointer< Array<int> > aj = getAdjacent(v); //得到v的邻接节点

                    //加入q队列
                    for(int j=0; j<aj->length(); j++)
                    {
                        q.add((*aj)[j]);
                    }

                    //v加入r队列并设置成已被访问过
                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r); //设置返回值
        }
        else
        {
            THROW_EXCEPTION(InvalidParamenterException, "Index i is invalid...");
        }

        return ret;
    }

    SharedPointer< Array<int> > dijkstra(int i, int j, const E& LIMIT)
    {
        LinkQueue<int> ret;

        if( (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) )
        {
            DynamicArray<E> dist(vCount()); //保存起始顶点到其他顶点间的权值
            DynamicArray<int> path(vCount()); //保存顶点的前驱顶点
            DynamicArray<bool> mark(vCount()); //标记顶点是否进入T集合

            for(int k=0; k<vCount(); k++)
            {
                mark[i] = false;
                path[i] = -1;

                dist[k] = isAdjacent(i, k) ? getEdge(i, k) : LIMIT; //判断是否邻接 如果是取出权值
            }

            mark[i] = true;

            for(int k=0; k<vCount(); k++)
            {
                E m = LIMIT;
                int u = -1;

                //找到目前dist数组内的最小值 这就得到了当前的最小路径
                for(int w=0; w<vCount(); w++)
                {
                    if( (!mark[w]) && (dist[w] < m) )
                    {
                        m = dist[w];
                        u = w;
                    }
                }

                if( u == -1 )
                {
                    break;
                }

                mark[u] = true; //放入T集合

                //通过已经找到的最小路径 去更新dist和path数组
                for(int w=0; w<vCount(); w++)
                {
                    if( (!mark[w]) && isAdjacent(u, w) && ((dist[u] + getEdge(u, w) < dist[w])))
                    {
                        dist[w] = dist[u] + getEdge(u, w);
                        path[w] = u;
                    }
                }
            }

            //通过栈 将得到的最短路径前后倒转
            LinkStack<int> s;

            s.push(j);

            for(int k=path[j]; k!=-1; k=path[k])
            {
                s.push(k);
            }

            while( s.size() > 0)
            {
                ret.add(s.top());
                s.pop();
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidParamenterException, "index(i, j) is invaild...");
        }

        if( ret.length() < 2 )
        {
            THROW_EXCEPTION(ArithmeticException, "There is no path i to j...");
        }

        return toArray(ret);
    }

    //基本流程和BFS类似 注释也类似
    SharedPointer< Array<int> > DFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if( (0 <= i) && (i < vCount()) )
        {
            LinkStack<int> s;
            LinkQueue<int> r;
            DynamicArray<int> visited(vCount());

            for(int j=0; j<visited.length(); j++)
            {
                visited[j] = false;
            }

            s.push(i);

            while( s.size() > 0 )
            {
                int v = s.top();

                s.pop();

                if( !visited[v] )
                {
                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    //这里变换一下位置 从后往前写入栈
                    for(int j=aj->length()-1; j>=0; j--)
                    {
                        s.push((*aj)[j]);
                    }

                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParamenterException, "Index i is invalid...");
        }

        return ret;
    }

    SharedPointer< Array<int> > floyd(int x, int y, const E& LIMIT)
    {
        LinkQueue<int> ret;

        if( (0 <= x) && (x < vCount()) && (0 <= y) && (y < vCount()) )
        {
            //创建这个二维数组的时候会报错
            DynamicArray< DynamicArray<E> > dist(vCount());
            //初始化路径矩阵 用于保存i到j路径上所经过的第一个顶点
            DynamicArray< DynamicArray<int> > path(vCount());

            //设置动态数组的长度
            for(int k=0; k<vCount(); k++)
            {
                dist[k].resize(vCount());
                path[k].resize(vCount());
            }

            //得到邻接矩阵
            for(int i=0; i<vCount(); i++)
            {
                for(int j=0; j<vCount(); j++)
                {
                    path[i][j] = -1;
                    dist[i][j] = isAdjacent(i, j) ? (path[i][j] = j, getEdge(i, j)) : LIMIT;
                }
            }

            //循环优化邻接矩阵
            for(int k=0; k<vCount(); k++)
            {
                for(int i=0; i<vCount(); i++)
                {
                    for(int j=0; j<vCount(); j++)
                    {
                        //如果经过k顶点的中转后 路径长度比原先的i到j小的话
                        if( (dist[i][k] + dist[k][j]) < dist[i][j] )
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            path[i][j] = path[i][k];
                        }
                    }
                }
            }

            //使用递推的方式 推导最短路径
            while( (x != -1) && (x != y) )
            {
                ret.add(x);
                x = path[x][y];
            }

            if( x != -1 )
            {
                ret.add(x);
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamenterException, "index(i, j) is invaild...");
        }

        if( ret.length() < 2 )
        {
            THROW_EXCEPTION(ArithmeticException, "There is no path i to j...");
        }

        return toArray(ret);
    }


};

}


#endif // GRAPH_H
