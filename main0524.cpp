/*
计算表达式——中缀转后缀算法
此算法分两步实现：先将算术表达式转换为后缀表达式，然后对后缀表达式进行计算。
*/

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int getISP(char ch)
{
    if(ch == '#')
        return 0;
    else if(ch == '(')
        return 1;
    else if((ch == '+') || (ch == '-'))
        return 3;
    else if((ch == '*') || (ch == '/') || (ch == '%'))
        return 5;
    else if(ch == ')')
        return 6;
    else
    {
        return -1;
    }
}
int getICP(char ch)
{
    if(ch == '#')
        return 0;
    else if(ch == '(')
        return 6;
    else if((ch == '+') || (ch == '-'))
        return 2;
    else if((ch == '*') || (ch == '/') || (ch == '%'))
        return 4;
    else if(ch == ')')
        return 1;
    else
    {
        return -1;
    }
}
string Convert(string expr)
{
    string::iterator it;
    string result = "";
    stack<char> op;
    op.push('#');
    for(it=expr.begin();it!=expr.end();it++)
    {
        char temp = *it;
        if(isdigit(temp) || temp == '.')
        {
            do{
                result += temp;
                temp = *(++it);
            }while(isdigit(temp) || temp == '.');
            it --;
            result += "#";
        }
        else if(getICP(temp) > getISP(op.top()))
        {
            op.push(temp);
        }
        else if(getICP(temp) < getISP(op.top()))
        {
            do{
                result += op.top();
                op.pop();
            }while(getICP(temp) < getISP(op.top()));

            if(getICP(temp) == getISP(op.top()))
            {
                op.pop();
            }
            else if(getICP(temp) > getISP(op.top()))
            {
                op.push(temp);
            }
        }
        else if(getICP(temp) == getISP(op.top()))
        {
            op.pop();
        }
    }
    while(op.top() != '#')
    {
        result += op.top();
        op.pop();
    }
    return result;
}
double Calculate(string expr)
{
    double operand1,operand2;
    stack<double> operand;
    string::iterator it;
    for(it=expr.begin();it!=expr.end();it++)
    {
        char c_temp = *it;
        string str = "";
        if(isdigit(c_temp) || c_temp == '.')
        {
            do{
                str += c_temp;
                c_temp = *(++it);
            }while(isdigit(c_temp) || c_temp == '.'); //因为数字都是以#号结束，所以迭代器无需回退
            stringstream io(str);
            double d_temp;
            io >> d_temp;
            operand.push(d_temp);
        }
        else
        {
            operand2 = operand.top(); //注意两个操作数的相对位置
            operand.pop();
            operand1 = operand.top();
            operand.pop();

            switch(c_temp)
            {
                case '+': operand.push(operand1 + operand2);break;
                case '-': operand.push(operand1 - operand2);break;
                case '*': operand.push(operand1 * operand2);break;
                case '/': operand.push(operand1 / operand2);break;
                //case '%': operand.push(operand1 % operand2);break;
                default: return -1;
            }
        }
    }
    return operand.top();
}
int main0524()
{
    string str = Convert("(35.67+4.34)*62-2+60/2");
    cout << str << endl;
    cout << Calculate(str);
    return 0;
}

