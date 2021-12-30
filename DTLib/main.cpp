#include <iostream>
#include "DTString.h"
#include <cstring>
#include "LinkList.h"
using namespace std;
using namespace DTLib;

int sum(int n)
{
    if( n > 1)
    {
        return n + sum(n - 1);
    }
    else if( n == 1)
    {
        return 1;
    }

    return 0;
}

int fac(int n)
{
    if( n >= 3)
    {
        return fac(n - 1) + fac(n - 2);
    }

    if( n == 2 )
    {
        return 1;
    }

    if( n == 1)
    {
        return 1;
    }

    return 0;
}

int _strlen_(char* s)
{
    if( *s != '\0' )
    {
        return 1 + _strlen_(s+1);
    }
    else if( *s == '\0')
    {
        return 0;
    }

    return 0;
}

//a: src
//b: middle
//c: dest
void HanoiTower(int n, char a, char b, char c)
{
    //当剩下一个的时候 直接将a移到c
    if( n == 1 )
    {
        cout << a << "-->" << c << endl;
    }
    else
    {
        HanoiTower(n-1, a, c, b); //首先将a上的积木以c为中转移到b
        HanoiTower(1, a, b, c);  //当只剩一个后 直接a移动到c
        HanoiTower(n-1, b, a, c); //然后将b上的积木以a为中转移到c
    }
}

//s指向全排序字符,e指向s的首地址
void permutation(char* s, char* e)
{
    //当递归到结束符时，打印s字符串
    if( *s == '\0' )
    {
        cout << e << endl;
    }
    else
    {
        int len = strlen(s);

        for(int i=0; i<len; i++)
        {
            //在进行交换之前
            //先判断要交换的位置上数字是否相同
            if( (i == 0) || (s[0] != s[i]) )
            {
                //交换位置后 重新计算子字符串的全字符排列
                swap(s[0], s[i]);
                permutation(s+1, e);
                swap(s[i], s[0]);
            }
        }

    }
}

template <int SIZE>
class QueueSolution : public Object
{
protected:
    enum { N = SIZE + 2 };

    struct Pos : public Object
    {
        Pos(int px=0, int py=0) : x(px), y(py) {}
        int x;
        int y;
    };

    int m_chessboard[N][N];   //定义棋盘 含边界
    Pos m_direction[3];       //定义三个要检查的方向
    LinkList<Pos> m_solution; //保存所有可用的点
    int m_count;              //保存解决方案的个数

    void init()
    {
        m_count = 0;

        //将棋盘的边界设置为2
        for(int i=0; i<N; i+=(N-1))
        {
            for(int j=0; j<N; j++)
            {
                m_chessboard[i][j] = 2;
                m_chessboard[j][i] = 2;
            }
        }

        //初始化棋盘值为0
        for(int i=1; i<=SIZE; i++)
        {
            for(int j=1; j<=SIZE; j++)
            {
                m_chessboard[i][j] = 0;
            }
        }

        //初始化要判断的三个方向 分别时左下 正下 右下
        m_direction[0].x = -1;
        m_direction[0].y = -1;
        m_direction[1].x = 0;
        m_direction[1].y = -1;
        m_direction[2].x = 1;
        m_direction[2].y = -1;
    }

    //打印棋盘
    void print()
    {
        for(m_solution.move(0); !m_solution.end(); m_solution.next())
        {
            cout << "(" << m_solution.current().x << " , " << m_solution.current().y << " ) " << endl;
        }

        cout << endl;

        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
                switch(m_chessboard[i][j])
                {
                    case 0: cout << " " ;      break;
                    case 1: cout << "#" ;      break;
                    case 2: cout << "*" ;      break;
                }
            }
            cout << endl;
        }

        cout << endl;
    }

    //校验位置是否合法
    bool check(int x, int y, int d)
    {
        bool flag = true;

        do
        {
            x += m_direction[d].x;
            y += m_direction[d].y;
            flag = flag && (m_chessboard[x][y] == 0); //判断这个方向上是否没有皇后
        }
        while( flag ); //当值为非0时会推出循环

        //判断一下最后是否到达了边界
        return (m_chessboard[x][y] == 2);
    }

    void run(int j)
    {
        if( j <= SIZE )
        {
            for(int i=1; i<=SIZE; i++)
            {
                //校验三个方向上是否合法
                if( check(i, j, 0) && check(i, j, 1) && check(i, j, 2) )
                {
                    m_chessboard[i][j] = 1;

                    m_solution.insert(Pos(i, j));

                    run(j+1); //继续校验下一个位置 如果不符合则移除当前位置 继续找下一个符合的位置

                    m_chessboard[i][j] = 0;

                    m_solution.remove(m_solution.length() - 1);
                }
            }
        }
        else
        {
            m_count++;

            print(); //j符合要求后 打印棋盘
        }
    }

public:
    QueueSolution()
    {
        init();
    }

    void run()
    {
        run(1);

        cout << "Total : " << m_count << endl;
    }
};

struct Test : public Object
{
    int key1; //高优先级
    int key2; //低优先级

    Test(int k1, int k2)
    {
        key1 = k1;
        key2 = k2;
    }

    bool operator == (const Test& t)
    {
        return (key1 == t.key1) && (key2 == t.key2);
    }

    bool operator !=(const Test& t)
    {
        return !(*this == t);
    }

    bool operator < (const Test& t)
    {
        return (key1 < t.key1) || ( (key1 == t.key1) && (key2 < t.key2));
    }

    bool operator >= (const Test& t)
    {
        return !(*this < t);
    }

    bool operator > (const Test& t)
    {
        return (key1 > t.key1) || ( (key1 == t.key1) && (key2 > t.key2));
    }

    bool operator <= (const Test& t)
    {
        return !(*this > t);
    }

};

int main()
{
    Test t1(3, 5);
    Test t2(3, 6);

    cout << (t1 < t2) << endl;

    return 0;
}
