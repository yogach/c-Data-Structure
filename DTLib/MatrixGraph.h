#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DTLib
{

template < int N, typename V, typename E >
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N]; //用于保存顶点
    E* m_edges[N][N]; //邻接矩阵 用于保存edge
    int m_eCount;

public:
    MatrixGraph()
    {
        for(int i=0; i<vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for(int j=0; j<vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }

            m_eCount = 0;
        }

    }

    V getVertex(int i)    //O(1)
    {
        V ret;

        if( !getVertex(i, ret) )
        {

           THROW_EXCEPTION(InvaildParamenterException, "index i is invaild...");

        }

        return ret;
    }

    bool getVertex(int i, V& value)  //O(1)
    {
        bool ret = ( (0 <=i ) && (i < vCount()) );

        if( ret )
        {
            if( m_vertexes[i] != NULL )
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvaildOperationException, "No value assigned to this vertex...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)  //O(1)
    {
        bool ret = ( (0 <=i ) && (i < vCount()) );

        if( ret )
        {
            V* data = m_vertexes[i]; //为了内存安全 使用中间变量来进行赋值

            if( data == NULL )
            {
                data = new V();
            }

            if( data != NULL )
            {
                *data = value; //此处的赋值可能因为V的不同导致异常发生

                m_vertexes[i] = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory to create new vertex...");
            }
        }

        return ret;
    }

    SharedPointer< Array<int> > getAdjacent(int i) // O(n)
    {
        DynamicArray<int>* ret = NULL;

        if( (0 <= i) && (i < vCount()) )
        {
            int n = 0;

            //首先得到有几条edge
            for(int j=0; j<vCount(); j++)
            {
                if( m_edges[i][j] != NULL)
                {
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);

            if( ret != NULL )
            {
                //之后将i的邻接顶点编号 写入到array内
                for(int j=0, k=0; j<vCount(); j++)
                {
                    if( m_edges[i][j] != NULL )
                    {
                        ret->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create dynamic array....");
            }
        }
        else
        {
            THROW_EXCEPTION(InvaildParamenterException, "index i is invaild...");
        }
        return ret;
    }

    E getEdge(int i, int j) //O(1)
    {
       E ret;

       if( !getEdge(i, j, ret) )
       {
           THROW_EXCEPTION(InvaildParamenterException, "index <i, j> is vaild...");
       }

       return ret;
    }

    bool getEdge(int i, int j, E& value)  //O(1)
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                     (0 <= j) && (i < vCount()) );

        if( ret )
        {
            if( m_edges[i][j] != NULL )
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvaildOperationException, "No value assigned to this edge...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)  //O(1)
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                     (0 <= j) && (i < vCount()) );

        if( ret )
        {
            E* ne = m_edges[i][j]; //使用中间变量保证异常安全

            if( ne == NULL )
            {
                ne = new E();

                if( ne != NULL )
                {
                    *ne = value;

                    m_edges[i][j] = ne;

                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "no memory to stroe new edge value...");
                }
            }
            else
            {
                *ne = value; //直接设置进去
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j)  //O(1)
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                     (0 <= j) && (i < vCount()) );

        if( ret )
        {
            E* todel = m_edges[i][j];

            m_edges[i][j] = NULL;

            if( todel != NULL )
            {
                m_eCount--;

                delete todel;
            }
        }

        return ret;
    }

    int vCount() //O(1)
    {
        return N;
    }

    int eCount() //O(1)
    {
        return m_eCount;
    }

    int OD(int i) //O(n)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            //统计边不为空的个树
            for(int j=0; j<vCount(); j++)
            {
                if( m_edges[i][j] != NULL )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvaildParamenterException, "index i is invaild...");
        }

        return ret;
    }

    int ID(int i)  //O(n)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            //统计边不为空的个树
            for(int j=0; j<vCount(); j++)
            {
                if( m_edges[j][i] != NULL )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvaildParamenterException, "index i is invaild...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for(int i=0; i<vCount(); i++)
        {
            for(int j=0; j<vCount(); j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }
};

}

#endif // MATRIXGRAPH_H
