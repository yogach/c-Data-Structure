#include <iostream>
#include "StaticList.h"

using namespace std;
using namespace DTLib;

int main()
{
    StaticList<int, 5> l;

    for(int i=0; i<l.capacity(); i++)
    {
        l.insert(0, i);
    }

    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << endl;
    }

    return 0;
}
