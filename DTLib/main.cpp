#include <iostream>
#include "SharedPointer.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    int value;
    Test() : value(0)
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

int main()
{
    SharedPointer<Test> sp = new Test();
    SharedPointer<Test> sp1 = sp;
    SharedPointer<Test> sp2 = NULL;
    const SharedPointer<Test> sp3 = new Test();

    sp2 = sp1;
    //sp3->value = 1; //此处会报错 因为无法修改const对象内容

    sp->value = 200;

    cout << sp->value << endl;
    cout << sp1->value << endl;
    cout << sp2->value << endl;

    sp2.clear();
    cout << (sp == sp2) << endl;

    return 0;
}
