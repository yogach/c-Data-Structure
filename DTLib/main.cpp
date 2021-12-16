#include <iostream>
#include "DTString.h"
using namespace std;
using namespace DTLib;


int main()
{
    String s = "this is test";

    cout << s.startWith("this") << endl;
    cout << s.startWith("a") << endl;
    cout << s.endOf("test") << endl;
    cout << s.endOf("ccc") << endl;


    for(int i=0; i<s.length(); i++)
    {
        cout << s[i] << endl;
    }

    String s1 = "";

    s1.insert(0,"insert test");

    cout << s1.str() << endl;


    String s2 = "  trim test ... ..   ";

    cout << s2.trim().str() << endl;


    return 0;
}
