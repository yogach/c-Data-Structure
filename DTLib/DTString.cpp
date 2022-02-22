#include "DTString.h"
#include <cstring>
#include <cstdlib>


namespace DTLib {

int* String::make_pmt(const char* p) //O(m)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if( ret != NULL )
    {
        int ll = 0;

        ret[0] = 0; //从pmt定义可得 1个字符的ll值肯定为0

        for(int i=1; i<len; i++)
        {
            while( (ll > 0) && (p[ll] != p[i]) )
            {
                ll = ret[ll - 1]; //通过递推的方式得到ll值
            }

            if( p[ll] == p[i] )
            {
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int String::kmp(const char* s, const char* p) //O(m) + O(n)
{
    int ret = -1;
    int sl = strlen(s);
    int pl =  strlen(p);
    int* pmt = make_pmt(p);

    if( (pmt != NULL) && (0 < pl) && (pl < sl) )
    {
        for(int i=0, j=0; i<sl; i++)
        {
            while( (j > 0) && (s[i] != p[j]) )
            {
                //这里实际上已经进行了缩写，原表达式为
                //j = j-(j-LL) = LL = PMT[j-1];
                j = pmt[j-1];
            }

            //当两者相等时 j++
            if( s[i] == p[j] )
            {
                j++;
            }

            //当j等于p长度时，p就是s的子串
            if( j == pl )
            {
                ret = i + 1 - pl; //返回p在s中的起始位置
                break;
            }
        }
    }

    free(pmt);

    return ret;
}



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
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid....");
    }

    return *this;
}

String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;

    //得到除了空格外字符串的起始位置
    while( m_str[b] == ' ') b++;
    while( m_str[e] == ' ') e++;

    if( b == 0)
    {
        m_str[e + 1] = '\0';
        m_length = e + 1;
    }
    else
    {
        for(int i=0, j=b; j<e; i++, j++)
        {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }

    return *this;
}

int String::indexOf(const char* s) const
{
    return kmp(m_str, s ? s : "");
}

int String::indexOf(const String& s) const
{
    return kmp(m_str, s.m_str);
}

String& String::remove(int i, int len)
{
    if( (0 <= i) && (i < m_length) )
    {
        int n = i; //得到起始删除位置
        int m = i + len; //得到结束位置

        //当m大于等于最大长度 说明原字符串已经结束了
        while( (n < m) && (m < m_length) )
        {
           m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
}

String& String::remove(const char* s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

String& String::remove(const String& s)
{
    return remove(s.m_str);
}

String& String::replace(const char* t, const char* s)
{
    int index = indexOf(t);

    //先删除 后插入
    if( index >= 0)
    {
        remove(t);
        insert(index, s);
    }

    return *this;
}

String& String::replace(const String& t, const char* s)
{
    return replace(t.m_str, s);
}

String& String::replace(const char* t, const String& s)
{
    return replace(t, s.m_str);
}

String& String::replace(const String& t, const String& s)
{
    return replace(t.m_str, s.m_str);
}

String String::sub(int i, int len) const
{
    String ret;

    if( (0 <= i) && (i < m_length) )
    {
        if( len < 0) len = 0;
        if( (len + i) > m_length)  len = m_length - i; //限制拷贝的最大长度不超过字符串长度
        char* str = reinterpret_cast<char*>(malloc(len + 1));

        strncpy(str, m_str+i, len);

        str[len] = '\0';

        ret = str;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "parameter is invalid...");
    }

    return ret;
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

String String::operator - (const String& s) const
{
    //使用本对象重新创建一个String临时对象，这样能保证原对象的内容不被删除
    return String(*this).remove(s);
}

String String::operator - (const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator -= (const String& s)
{
    return remove(s);
}

String& String::operator -= (const char* s)
{
    return remove(s);
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
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid....");
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


