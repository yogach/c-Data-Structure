#include <iostream>
#include "Sort.h"
#include "DynamicArray.h"

using namespace std;
using namespace DTLib;


int main()
{
   /* int a[] = {2,345,671,222,333, 10, 12 , 100, 95};

    Sort::Quick(a, 9, false);

    for(int i=0; i<9; i++)
    {
        cout << a[i] << endl;
    } */

    DynamicArray<double> da(10);

    for(int i=0; i<10; i++)
    {
        da[i] = i;
    }

    Sort::Bubble(da, false);

    for(int i=0; i<10; i++)
    {
        cout << da[i] << endl;
    }

    return 0;
}
