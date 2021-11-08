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
        list.set(0, i*i);
    }

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << endl;
    }

    list.remove(2);

    cout << endl;

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << endl;
    }


    return 0;
}
