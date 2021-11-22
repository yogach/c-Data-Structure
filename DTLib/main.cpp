#include <iostream>
#include "CircleList.h"

using namespace std;
using namespace DTLib;

//约瑟夫问题的解法
void josephus(int n, int s, int m)
{
    CircleList<int> cl;

    for(int i=1; i<=n; i++)
    {
        cl.insert(i);
    }

    cl.move(s-1, m-1); //从s位置开始 每次移动m-1个

    while( cl.length() > 0)
    {
        cl.next(); //m_current指向下一个节点

        cout << cl.current() << endl;

        cl.remove(cl.find(cl.current())); //移除当前节点
    }
}

int main()
{
    josephus(41, 1, 3);

    return 0;
}
