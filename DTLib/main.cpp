#include <iostream>
#include "DTString.h"
#include <cstring>
using namespace std;
using namespace DTLib;

int* make_pmt(const char* p) //O(m)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if( ret != NULL )
    {
        int ll = 0;

        ret[0] = 0; //从pmt定义可得 1个字符的ll值肯定为0

        for(int i=1; i<len; i++)
        {
            while( (ll > 0) && (p[ll] != p[i]) )
            {
                ll = ret[ll - 1]; //通过递推的方式得到ll值
            }

            if( p[ll] == p[i] )
            {
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int kmp(const char* s, const char* p) //O(m) + O(n)
{
    int ret = -1;
    int sl = strlen(s);
    int pl =  strlen(p);
    int* pmt = make_pmt(p);

    if( (pmt != NULL) && (0 < pl) && (pl < sl) )
    {
        for(int i=0, j=0; i<sl; i++)
        {
            while( (j > 0) && (s[i] != p[j]) )
            {
                //这里实际上已经进行了缩写，原表达式为
                //j = j-(j-LL) = LL = PMT[j-1];
                j = pmt[j-1];
            }

            //当两者相等时 j++
            if( s[i] == p[j] )
            {
                j++;
            }

            //当j等于p长度时，p就是s的子串
            if( j == pl )
            {
                ret = i + 1 - pl; //返回p在s中的起始位置
                break;
            }
        }
    }

    free(pmt);

    return ret;
}

int main()
{
    cout << kmp("abcde", "cde") << endl;

    return 0;
}
