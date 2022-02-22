#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace DTLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;

    void init(const char* message, const char* file, int line);
public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator = (const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0; //声明析构函数为纯虚函数 实际上还是需要手动实现
};


class ArithmeticException : public Exception
{
public:
    ArithmeticException(const char* message) : Exception(message) {}
    ArithmeticException(const char* file, int line) : Exception(file, line) {}
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    ArithmeticException(const ArithmeticException& e) : Exception(e) {}
    ArithmeticException& operator = (const ArithmeticException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

class NullPointException : public Exception
{
public:
    NullPointException(const char* message) : Exception(message) {}
    NullPointException(const char* file, int line) : Exception(file, line) {}
    NullPointException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    NullPointException(const NullPointException& e) : Exception(e) {}
    NullPointException& operator = (const NullPointException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException(const char* message) : Exception(message) {}
    IndexOutOfBoundsException(const char* file, int line) : Exception(file, line) {}
    IndexOutOfBoundsException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) {}
    IndexOutOfBoundsException& operator = (const IndexOutOfBoundsException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException(const char* message) : Exception(message) {}
    NoEnoughMemoryException(const char* file, int line) : Exception(file, line) {}
    NoEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    NoEnoughMemoryException(const NoEnoughMemoryException& e) : Exception(e) {}
    NoEnoughMemoryException& operator = (const NoEnoughMemoryException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

class InvalidParamenterException : public Exception
{
public:
    InvalidParamenterException(const char* message) : Exception(message) {}
    InvalidParamenterException(const char* file, int line) : Exception(file, line) {}
    InvalidParamenterException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    InvalidParamenterException(const InvalidParamenterException& e) : Exception(e) {}
    InvalidParamenterException& operator = (const InvalidParamenterException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};


class InvalidOperationException : public Exception
{
public:
    InvalidOperationException(const char* message) : Exception(message) {}
    InvalidOperationException(const char* file, int line) : Exception(file, line) {}
    InvalidOperationException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    InvalidOperationException(const InvalidOperationException& e) : Exception(e) {}
    InvalidOperationException& operator = (const InvalidOperationException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

}

#endif // EXCEPTION_H
