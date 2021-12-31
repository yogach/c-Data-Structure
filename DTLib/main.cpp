#include <iostream>
#include "Sort.h"

using namespace std;
using namespace DTLib;


int main()
{
    int a[] = {2,345,671,222,333, 10};

    Sort::Select(a, 6, false);

    for(int i=0; i<6; i++)
    {
        cout << a[i] << endl;
    }

    return 0;
}
