#include <iostream>
#include "StaticQueue.h"

using namespace std;
using namespace DTLib;

int main()
{
    StaticQueue<int, 5> queue;

    for(int i=0; i<5; i++)
    {
        queue.add(i);
    }

    for(int i=0; i<5; i++)
    {
        cout << queue.front() << endl;

        queue.remove();
    }

    return 0;
}
