#include <iostream>
#include "DynamicList.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main()
{
    DynamicList<int> l(5);

    for(int i=0; i<l.capacity(); i++)
    {
        l.insert(0, i);
    }

    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << endl;
    }

    try
    {
        l[5] = 5;
    }
    catch(const Exception& e)
    {
        cout << e.message() << endl;
        cout << e.location() << endl;

        l.resize(10);
        l.insert(5, 501);
    }

    l[5] = 5;

    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << endl;
    }

    l.resize(3);

    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << endl;
    }


    return 0;
}
