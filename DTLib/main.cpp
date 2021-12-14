#include <iostream>
#include "DTString.h"
using namespace std;
using namespace DTLib;

void test_1()
{
    cout << "test()_1 begin..." << endl;

    String s;

    s = 'D';

    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (s == "D") << endl;
    cout << (s > "CCC") << endl;

    s += " this is another ";
    cout << s.str() << endl;
    cout << s.length() << endl;

    cout << "test()_1 end..." << endl;
}

void test_2()
{
    cout << "test()_2 begin..." << endl;

    String a[] = {"E", "F", "G", "A", "Z"};
    String min = a[0];

    for(int i=0; i<5; i++)
    {
        if( min > a[i] )
        {
            min = a[i];
        }
    }

    cout << "min = " << min.str() << endl;

    cout << "test()_2 end..." << endl;
}

int main()
{  
    test_1();
    test_2();
    return 0;
}
