#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"
#include "LinkList.h"

namespace DTLib
{

template < typename V, typename E >
class ListGraph : public Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;
        LinkList< Edge<E> > edge; //edge链表

        Vertex()
        {
            data = NULL;
        }
    };

    LinkList< Vertex*> m_list; //顶点链表

public:
    //构造函数 创建n个顶点
    ListGraph(unsigned int n = 0)
    {
        for(unsigned int i=0; i<n; i++)
        {
            addVertex();
        }
    }

    //新增顶点 只能加在最后
    int addVertex()   //O(n)
    {
        int ret = -1;
        Vertex* v = new Vertex();

        if( v != NULL )
        {
            m_list.insert(v);

            ret = m_list.length() - 1; //返回顶点的编号
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to add new Vertex...");
        }


        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = addVertex();

        if( ret >= 0 )
        {
            setVertex(ret, value);
        }

        return ret;
    }

    bool setVertex(int i, const V& value) //O(n)
    {
        bool ret = ( (0 <= i) && (i < vCount()) );

        if( ret )
        {
            Vertex* vertex = m_list.get(i);
            V* data = vertex->data;

            if( data == NULL )
            {
                data = new V();
            }

            if( data != NULL )
            {
                *data = value;

                vertex->data = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new vertex value...");
            }

        }

        return ret;
    }

    V getVertex(int i) //O(n)
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParamenterException, "index i is invalid...");
        }

        return ret;
    }

    bool getVertex(int i, V& value) //O(n)
    {
        bool ret = ( (0 <= i) && (i < vCount()) );

        if( ret )
        {
            Vertex* vertex = m_list.get(i);

            if( vertex->data != NULL )
            {
                value = *(vertex->data);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex...");
            }
        }

        return ret;
    }

    //只能移除最后一个添加的节点
    void removeVertex()  //O(n*n)
    {
        if( m_list.length() > 0 )
        {
            int index = m_list.length() - 1;
            Vertex* v = m_list.get(index);

            if( m_list.remove(index) )
            {
                //首先遍历所有顶点的邻接链表 有没有和需要删除顶点相关的edge
                for(int i=(m_list.move(0), 0); !m_list.end(); i++, m_list.next())
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));

                    //如果有找到则删除这条边
                    if( pos >= 0 )
                    {
                        m_list.current()->edge.remove(pos);
                    }
                }

                //释放空间
                delete v->data;
                delete v;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in this graph...");
        }
    }
    
    SharedPointer< Array<int> > getAdjacent(int i) //O(n)
    {
        DynamicArray<int>* ret = NULL;
        
        if( (0 <= i ) && (i < vCount()) )
        {
            Vertex* v = m_list.get(i);            
            ret = new DynamicArray<int>(v->edge.length()); //直接使用邻接矩阵的长度分配数组长度
                                    
            if( ret != NULL )
            {
                //遍历邻接矩阵 得到终点数据 并写入到返回数组
                for(int k=(v->edge.move(0), 0); !v->edge.end(); k++, v->edge.next())
                {
                    ret->set(k, v->edge.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create array...");
            }            
        }
        else
        {
            THROW_EXCEPTION(InvalidParamenterException, "index i is vaild...");
        }
        
        return ret;
    }
    
    E getEdge(int i, int j)
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParamenterException, "Edge(i, j) is invalid...");
        }
        
        return ret;
    }
    
    bool getEdge(int i, int j, E& value) //O(n)
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );

        if( ret )
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));

            if( pos >= 0 )
            {
                value = vertex->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "no value assigned to this edge... ");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)  //O(n)
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                     (0 <= j) && (j < vCount()) );

        if( ret )
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));

            if( pos >= 0 )
            {
               ret = vertex->edge.set(pos, Edge<E>(i, j, value) );
            }
            else
            {
               ret = vertex->edge.insert(0, Edge<E>(i, j, value));
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j) //O(n)
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                     (0 <= j) && (j < vCount()) );

        if( ret )
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));

            if( pos >= 0 )
            {
                ret = vertex->edge.remove(pos);
            }
        }

        return ret;
    }

    int vCount() //O(n)
    {
        //顶点数 直接返回 顶点链表长度
        return m_list.length();
    }

    int eCount() //O(n)
    {
        int ret = 0;

        //边数量 统计所有顶点的邻接链表长度
        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current()->edge.length();
        }

        return ret;
    }

    //一个顶点的入度=每个顶点邻接链表内终点为i的数量
    int ID(int i) //O(n*n)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            for(m_list.move(0); !m_list.end(); m_list.next())
            {
                LinkList< Edge<E> >&  e = m_list.current()->edge;

                for( e.move(0); !e.end(); e.next() )
                {
                    if( e.current().e == i )
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamenterException, "index i is invalid...");
        }

        return ret;
    }

    //顶点的出度：邻接链表的长度
    int OD(int i)  //O(n)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            Vertex* vertex = m_list.get(i);

            ret = vertex->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParamenterException, "index i is invalid...");
        }

        return ret;
    }

    ~ListGraph()
    {
        while( m_list.length() > 0)
        {
            Vertex* toDel = m_list.get(0); //每次都删除0位置上的节点

            m_list.remove(0);

            //释放分配的空间
            delete toDel->data;
            delete toDel;
        }
    }
};

}

#endif // LISTGRAPH_H
