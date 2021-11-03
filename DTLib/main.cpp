#include <iostream>
#include "DynamicArray.h"

using namespace std;
using namespace DTLib;

int main()
{
    DynamicArray<int> a1(5);

    for(int i=0; i<a1.length(); i++)
    {
        a1[i] = i * i;
    }

    for(int i=0; i<a1.length(); i++)
    {
        cout << a1[i] << endl;
    }

    DynamicArray<int> a2(10);

    a2 = a1;

    for(int i=0; i<a2.length(); i++)
    {
        cout << a2[i] << endl;
    }

    a1.resize(3);

    for(int i=0; i<a1.length(); i++)
    {
        cout << a1[i] << endl;
    }



    return 0;
}
