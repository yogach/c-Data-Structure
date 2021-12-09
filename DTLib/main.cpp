#include <iostream>
#include "LinkQueue.h"

using namespace std;
using namespace DTLib;

int main()
{
    LinkQueue<int> lq;

    for(int i=0; i<5; i++)
    {
        lq.add(i);
    }

    while( lq.length() > 0)
    {
        cout << lq.front() << endl;

        lq.remove();
    }

    return 0;
}
