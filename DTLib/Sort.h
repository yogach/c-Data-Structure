#ifndef SORT_H
#define SORT_H

#include "Object.h"

namespace DTLib {

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template <typename T>
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

public:
    //这是一个不稳定的排序算法
    template <typename T>
    static void Select(T array[], int len, bool min2max = true)
    {
        for(int i=0; i<len; i++)
        {
            //将第i个位置上的数据和之后所有的数据进行比较
            int min = i;
            for(int j=i; j<len; j++)
            {
                if( min2max ? (array[min] > array[j]) : (array[min] < array[j]) )
                {
                    min = j;
                }
            }

            //得到最小的之后 进行交换
            if( i != min)
               Swap(array[i], array[min]);
        }
    }

};

}

#endif // SORT_H
