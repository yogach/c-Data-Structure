#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
    int i;
public:
    Test(int v = 0)
    {
        i = v;
    }

    bool operator == (const Test& e)
    {
        return (i == e.i);
    }
};

int main()
{
    Test t1(1);
    Test t2(2);
    Test t3(3);

    LinkList<Test> list;

    list.insert(t1);
    list.insert(t2);
    list.insert(t3);

    cout << list.find(3) << endl;


    return 0;
}
