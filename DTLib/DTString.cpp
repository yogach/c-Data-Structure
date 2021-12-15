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

bool String::equal(const char* l, const char* r, int len) const
{
    bool ret = true;

    for(int i=0; i<len; i++)
    {
        //当有不等于的时候直接退出
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

const char* String::str() const
{
    return m_str;
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);

    if( ret )
    {
        int len = strlen(s);

        //判断s的长度是否小于总的字符串长度 之后在判断两者是否相同
        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);

    if( ret )
    {
        int len = strlen(s);
        char* str = m_str + (m_length - len);

        //判断s的长度是否小于总的字符串长度 之后在判断两者是否相同
        ret = (len < m_length) && equal(str, s, len);
    }

    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int i, const char* s)
{
    if( (0 <= i) && (i <= m_length) )
    {
        //判断s不为空指针和空字符串
        if( (s != NULL) && (s[0] != '\0') )
        {
            int len = strlen(s) ;
            char* str = reinterpret_cast<char*>(malloc(len + m_length + 1));

            if( str != NULL )
            {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);

                str[m_length + len] = '\0';

                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to insert string...");
            }

        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invaild....");
    }

    return *this;
}

String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
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

char& String::operator [](int i)
{
    if( (0 <= i) && (i < m_length) )
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invaild....");
    }
}

char String::operator [](int i) const
{
    return (const_cast<String&>(*this))[i]; //使用const_cast去除只读属性
}


String::~String()
{
    free(m_str);
}

}


