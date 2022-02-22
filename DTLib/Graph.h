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
