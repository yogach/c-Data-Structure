#include <iostream>
#include "StaticStack.h"

using namespace std;
using namespace DTLib;


int main()
{
    StaticStack<int, 5> stack;

    for(int i=0; i<5; i++)
    {
        stack.push(i);
    }

    while( stack.size() > 0 )
    {
        cout << stack.top() << endl;

        stack.pop();
    }

    return 0;
}
