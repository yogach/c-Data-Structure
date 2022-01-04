#include <iostream>
#include "Sort.h"

using namespace std;
using namespace DTLib;


int main()
{
    int a[] = {2,345,671,222,333, 10};

    Sort::Merge(a, 6, true);

    for(int i=0; i<6; i++)
    {
        cout << a[i] << endl;
    }

    return 0;
}
