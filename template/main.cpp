#include <iostream>

using namespace std;

template <typename T>
void Swap(T& a, T& b)
{
    T c = a;
    a = b;
    b = c;
}

template <typename T>
class op
{
public:
    T process(T v)
    {
        return v * v;
    }

};

int main()
{
    int a = 1, b = 2;

    Swap(a, b);

    cout << "a = " << a << " " << " b = " << b << endl;

    double c = 0.01;
    double d = 0.02;

    Swap<double>(d, c);

    cout << "c = " << c << " " << "d = " << d << endl;

    op<int> opInt;
    op<double> opDouble;

    cout << "5 * 5 = " << opInt.process(5) << endl;
    cout << "0.3 * 0.3 = " << opDouble.process(0.3) << endl;


    return 0;
}
