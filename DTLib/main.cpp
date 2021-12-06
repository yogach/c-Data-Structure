#include <iostream>
#include "LinkStack.h"

using namespace std;
using namespace DTLib;

bool is_left(char c)
{
    return (c == '(') || (c == '{') || (c == '[') || (c == '<');
}

bool is_right(char c)
{
    return (c == ')') || (c == '}') || (c == ']') || (c == '>');
}

bool is_quot(char c)
{
    return (c == '\'') || (c == '\"');
}

bool is_match(char l, char r)
{
    return ( (l == '(') && (r == ')') ) ||
            ( (l == '{') && (r == '}') ) ||
            ( (l == '[') && (r == ']') ) ||
            ( (l == '<') && (r == '>') ) ||
            ( (l == '\'') && (r == '\'') ) ||
            ( (l == '\"') && (r == '"') ) ;
}

bool scan(const char* code)
{
    LinkStack<char> stack;
    int i=0;
    bool ret = true;

    code = (code == NULL) ? "" : code;

    while( ret && (code[i] != '\0') )
    {
        if( is_left(code[i]) )
        {
            stack.push(code[i]);
        }
        else if( is_right(code[i]) )
        {
            //如果当前栈内有数据 并且和栈顶元素匹配 则出栈
            if( ( stack.size() > 0)  && is_match(stack.top(), code[i]) )
            {
                stack.pop();
            }
            else
            {
                ret = false;
            }
        }
        else if( is_quot(code[i]) )
        {
            //如果当前栈内无数据或栈顶元素不是冒号 压栈
            if( (stack.size() == 0) || !is_match(stack.top(), code[i]) )
            {
                stack.push(code[i]);
            }
            else if( is_match(stack.top(), code[i]) )
            {
                stack.pop();
            }
        }

        i++;
    }


    return ret && (stack.size() == 0);
}

int main()
{
    cout << scan("(aaa[aa{a}a])a") << endl;

    return 0;
}
