#include <iostream>
#include "StaticArray.h"

using namespace std;
using namespace DTLib;

int main()
{
    StaticArray<int, 5> a1;

    for(int i=0; i<a1.length(); i++)
    {
        a1[i] = i * i;
    }

    for(int i=0; i<a1.length(); i++)
    {
        cout << a1[i] << endl;
    }

    StaticArray<int, 5> a2;

    a2 = a1;

    for(int i=0; i<a2.length(); i++)
    {
        cout << a2[i] << endl;
    }

    a2[6] = 100;

    return 0;
}
