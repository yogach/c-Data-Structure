#include <iostream>
#include "DTString.h"
#include <cstring>
using namespace std;
using namespace DTLib;


int main()
{
    String s("abcdef");

    cout << s.indexOf("cdef") << endl;
    return 0;
}
