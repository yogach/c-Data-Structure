#include <iostream>
#include "DualCircleList.h"

using namespace std;
using namespace DTLib;


int main()
{
    DualCircleList<int> dl;

    for(int i=0; i<5; i++)
    {
        dl.insert(0, i);
        dl.insert(0, 5);
    }

    cout << "start" << endl;

    dl.move(dl.length() - 1);

    while ( dl.find(5) != -1 )
    {
        if( dl.current() == 5)
        {
            cout << dl.current() << endl;
            dl.remove(dl.find( dl.current() ));
        }
        else
        {
            dl.pre();
        }
    }

    cout << "end" << endl;

    int i;
    for(i=0, dl.move(0); !dl.end() && (i < dl.length()); dl.next(), i++)
    {
        cout << dl.current() << endl;
    }

    return 0;
}
