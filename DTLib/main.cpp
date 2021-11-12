#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace DTLib;


int main()
{
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(0, i);
    }

    for(list.move(0); !list.end(); list.next())
    {
        cout << list.current() << endl;
    }

    return 0;
}
