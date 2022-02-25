#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Exception.h"

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

    SharedPointer< Array< Edge<E> > > prim(const E& LIMIT)
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
                    if( !mark[j] && (cost[j] < m) )
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
                        if( !mark[(*aj)[j]] && (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]) )
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


};

}


#endif // GRAPH_H
