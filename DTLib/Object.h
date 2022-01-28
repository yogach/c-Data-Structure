#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>

using namespace std;

namespace DTLib {

class Object
{
public:
    void* operator new(size_t size) throw(); //带throw() 代表此函数不会抛出异常
    void operator delete(void* p);
    void* operator new[] (size_t size) throw();
    void operator delete[] (void* p);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object() = 0;   //析构函数声明成虚函数 子类将支持动态类型识别 dynamic_cast
};

}


#endif // OBJECT_H
