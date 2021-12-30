#ifndef SORT_H
#define SORT_H

#include "Object.h"

namespace DTLib {

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template <typename T>
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

};

}

#endif // SORT_H
