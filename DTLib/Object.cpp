#include "Object.h"
#include <cstdlib>

using namespace std;

namespace DTLib {

//throw关键字代表 此函数不会抛出异常
void* Object::operator new(long unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete(void* p)
{
    free(p);
}

void* Object::operator new[] (long unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

bool Object::operator == (const Object& obj)
{
    return (this == &obj);
}

bool Object::operator != (const Object& obj)
{
    return (this != &obj);
}


Object::~Object()
{

}


}
