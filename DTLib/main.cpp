#include <iostream>
#include "DualLinkList.h"

using namespace std;
using namespace DTLib;


int main()
{
    DualLinkList<int> dl;

    for(int i=0; i<5; i++)
    {
        dl.insert(0, i);
        dl.insert(0, 5);
    }

    cout << "start" << endl;

    dl.move(dl.length() - 1);

    while ( !dl.end() ) {
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

    for(dl.move(0); !dl.end(); dl.next())
    {
        cout << dl.current() << endl;
    }

    return 0;
}
