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
				if(it!=(expr.end()-1))
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
				if(it!=(expr.end()-1))
					c_temp = *(++it);
            }while(isdigit(c_temp) || c_temp == '.');
            stringstream io(str);
            double d_temp;
            io >> d_temp;
            operand.push(d_temp);
        }
        else
        {
            operand1 = operand.top();
            operand.pop();
            operand2 = operand.top();
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
int main0001()
{
    string str = Convert("(35.67+4.34)*62-2+60/2");
    cout << str << endl;
    cout << Calculate(str);
    return 0;
}