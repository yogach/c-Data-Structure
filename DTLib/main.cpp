#include <iostream>
#include "DTString.h"
#include <cstring>
using namespace std;
using namespace DTLib;


int main()
{
    String s("abcdef");
    String s1 = s - "abc";

    cout << s.str() << endl;
    cout << s1.str() << endl;

    cout << s.replace("ab", "xxxxx").str() << endl;

    return 0;
}
