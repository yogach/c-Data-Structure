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

class InvaildParamenterException : public Exception
{
public:
    InvaildParamenterException(const char* message) : Exception(message) {}
    InvaildParamenterException(const char* file, int line) : Exception(file, line) {}
    InvaildParamenterException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    InvaildParamenterException(const InvaildParamenterException& e) : Exception(e) {}
    InvaildParamenterException& operator = (const InvaildParamenterException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};


class InvaildOperationException : public Exception
{
public:
    InvaildOperationException(const char* message) : Exception(message) {}
    InvaildOperationException(const char* file, int line) : Exception(file, line) {}
    InvaildOperationException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    InvaildOperationException(const InvaildOperationException& e) : Exception(e) {}
    InvaildOperationException& operator = (const InvaildOperationException& e)
    {
        Exception::operator =(e);

        return *this;
    }

};

}

#endif // EXCEPTION_H
