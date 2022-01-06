#include <iostream>
#include "Sort.h"

using namespace std;
using namespace DTLib;


int main()
{
    int a[] = {2,345,671,222,333, 10, 12 , 100, 95};

    Sort::Quick(a, 9, false);

    for(int i=0; i<9; i++)
    {
        cout << a[i] << endl;
    }

    return 0;
}
