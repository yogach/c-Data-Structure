#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

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

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max = true)
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;

        while( (i <= mid) && (j <= end) )
        {
            //分别对两个序列的元素进行比较 符合要求的放入辅助空间
            if( min2max ? (src[i] < src[j]) :  (src[i] > src[j]))
            {
                helper[k++] = src[i++];
            }
            else
            {
                helper[k++] = src[j++];
            }
        }

        //将两个序列合并剩下的元素 一并拷贝到辅助空间
        while( i <= mid)
        {
            helper[k++] = src[i++];
        }

        while( j <= end)
        {
            helper[k++] = src[j++];
        }

        //将辅助空间内容拷贝到src内
        for(i=begin; i<=end; i++)
        {
            src[i] = helper[i];
        }
    }

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool min2max = true)
    {
        //递归的终止条件
        if( begin == end )
        {
            return ;
        }
        else
        {
            int mid = (begin + end) / 2; // 现在实现的是两路归并排序

            //对左右两路分别进行归并排序 最后合并两个有序序列
            Merge(src, helper, begin, mid, min2max);
            Merge(src, helper, mid+1, end, min2max);
            Merge(src, helper, begin, mid, end, min2max);
        }
    }

    //找到基准元素 并将原始序列划分成一个比基准元素大 一个比基准元素小
    template < typename T >
    static int Partition(T array[], int begin, int end, bool min2max)
    {
        T pv = array[begin]; //首先找到一个基准元素

        while( begin < end )
        {
            //从后往前查找比pv小的值
            while( (begin < end) && (min2max ? (array[end] > pv) : (array[end] < pv)) )
            {
                end--;
            }

            //也可能会交换自身
            Swap( array[begin], array[end] ); //找到则交换

            //从前往后查找比pv大的值
            while( (begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] >= pv)) )
            {
                begin++;
            }

            //也可能会交换自身
            Swap( array[begin], array[end] ); //找到则交换
        }

        array[begin] = pv;

        return begin;
    }

    template < typename T >
    static void Quick(T array[], int begin, int end, bool min2max)
    {
        //使用递归的方式分别
        if( begin < end )
        {
            int pivot = Partition(array, begin, end, min2max);

            Quick(array, begin, pivot-1, min2max);
            Quick(array, pivot+1, end, min2max);
        }
    }

public:
    //这是一个不稳定的排序算法
    template <typename T>
    static void Select(T array[], int len, bool min2max = true) //O(n^2)
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

    template <typename T>
    static void Insert(T array[], int len, bool min2max = true) //O(n^2)
    {
        for(int i=1; i<len; i++)
        {
            int k = i;
            T e = array[i]; //首先将要排序的元素取出来

            //从当前位置往前查找
            for(int j=i-1; (j>=0) && (min2max ? (array[j] > e) : (array[j] < e)); j--)
            {
               array[j+1] = array[j]; //将符合要求的数据往后移动一个位置
               k = j; //记录下数组内空出的位置
            }

            //假设元素需要移动 则进行拷贝操作
            if( k != i )
            {
                array[k] = e;
            }
        }
    }

    template <typename T>
    static void Bubble(T array[], int len, bool min2max = true) //O(n^2)
    {
        bool exchange = true; //使用标志位来标记剩下的元素是否已经组成了有序序列

        for(int i=0; (i<len) && exchange; i++)
        {
            exchange = false;

            //从后往前冒泡
            for(int j=len-1; j>i; j--)
            {
                //比较前后两个元素的大小 不符合则交换两者位置
                if( min2max ? (array[j] < array[j-1]) : (array[j] > array[j-1]))
                {
                    Swap(array[j], array[j-1]);
                    exchange = true;
                }
            }
        }
    }

    template <typename T>
    static void Shell(T array[], int len, bool min2max = true) //O(n^(3/2))
    {
        int d = len;

        do
        {
            d = d / 3 + 1; //希尔排序关键参数 将数组

            //之后就是完整的插入排序
            for(int i=d; i<len; i+=d)
            {
                int k = i;
                T e = array[i]; //首先将要排序的元素取出来

                //从当前位置往前查找
                for(int j=i-d; (j>=0) && (min2max ? (array[j] > e) : (array[j] < e)); j-=d)
                {
                   array[j+d] = array[j]; //将符合要求的数据往后移动一个位置
                   k = j; //记录下数组内空出的位置
                }

                //假设元素需要移动 则进行拷贝操作
                if( k != i )
                {
                    array[k] = e;
                }
            }

        } while( d > 1);
    }

    template <typename T>
    static void Merge(T array[], int len, bool min2max = true)
    {
        T* helper = new T[len]; //申请一个辅助空间

        if( helper != NULL )
        {
            Merge(array, helper, 0, len-1, min2max);
        }

        delete[] helper;
    }

    template < typename T >
    static void Quick(T array[], int len, bool min2max = true)
    {
        Quick(array, 0, len-1, min2max);
    }

    template < typename T>
    static void Select(Array<T>& array, bool min2max = true)
    {
        Select(array.array(), array.length(), min2max);
    }

    template < typename T>
    static void Insert(Array<T>& array, bool min2max = true)
    {
        Insert(array.array(), array.length(), min2max);
    }

    template < typename T>
    static void Bubble(Array<T>& array, bool min2max = true)
    {
        Bubble(array.array(), array.length(), min2max);
    }

    template < typename T>
    static void Shell(Array<T>& array, bool min2max = true)
    {
        Shell(array.array(), array.length(), min2max);
    }

    template < typename T>
    static void Merge(Array<T>& array, bool min2max = true)
    {
        Merge(array.array(), array.length(), min2max);
    }

    template < typename T>
    static void Quick(Array<T>& array, bool min2max = true)
    {
        Quick(array.array(), array.length(), min2max);
    }



};

}

#endif // SORT_H
