#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;



int main()
{
    try
    {
       THROW_EXCEPTION(ArithmeticException, "test");
    }
    catch(const ArithmeticException e)
    {
        cout << "const ArithmeticException e" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    return 0;
}
