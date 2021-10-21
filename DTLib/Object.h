#ifndef OBJECT_H
#define OBJECT_H

namespace DTLib {


class Object
{
public:
    void* operator new(long unsigned int size) throw(); //带throw() 代表此函数不会抛出异常
    void operator delete(void* p);
    void* operator new[] (long unsigned int size) throw();
    void operator delete[] (void* p);
    virtual ~Object() = 0;   //析构函数声明成虚函数 子类将支持动态类型识别 dynamic_cast
};

}


#endif // OBJECT_H
