#include "DTString.h"
#include <cstring>
#include <cstdlib>


namespace DTLib {

void String::init(const char* s)
{
    m_str = strdup(s); //拷贝一份字符串

    if( m_str )
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new string object...");
    }

}

String::String()
{
    init("");
}

String::String(char c)
{
    char s[] = {c, '\0'};

    init(s);
}

String::String(const char* s)
{
    init(s ? s : "");
}

String::String(const String& s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

bool String::operator == (const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool String::operator == (const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator != (const String& s) const
{
    return !(*this == s); //直接调用之前实现的 == 操作符重载
}

bool String::operator != (const char* s) const
{
    return !(*this == s);
}

bool String::operator > (const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool String::operator > (const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator < (const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}

bool String::operator < (const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator >= (const String& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}

bool String::operator >= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator <= (const String& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}

bool String::operator <= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}


String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
   String ret;
   int len = m_length + strlen(s ? s : "");
   char* str = reinterpret_cast<char*>(malloc(len + 1)); // +1为了放结束符

   if( str )
   {
       strcpy(str, m_str);
       strcat(str, s ? s : "");

       free(ret.m_str);

       ret.m_str = str;
       ret.m_length = len;
   }
   else
   {
       THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new string object...");
   }

   return ret;
}

String& String::operator += (const String& s)
{
    return (*this = *this + s); //此处涉及到 = 和 + 的操作符重载
}

String& String::operator += (const char* s)
{
    return (*this = *this + s);
}

String& String::operator = (const String& s)
{
    return (*this = s.m_str);
}

String& String::operator = (const char* s)
{
    if( m_str != s)
    {
        char* str = strdup(s ? s : "");

        if( str )
        {
            free(m_str);

            m_str = str; //此处是直接的指针操作
            m_length = strlen(str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to assgin new Strinf value...");
        }

    }

    return *this;

}

String& String::operator = (char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

String::~String()
{
    free(m_str);
}

}


