#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*******************************************************************
Ex_5_1:
空语句就是只含有一个分号的语句。
如果在程序的某个地方，语法上要求有一条语句，但是逻辑上不需要，
这时就需要一条空语句。
Ex_5_2:
块就是由花括号包围的复合语句。
如果在程序的某个地方，语法上要求有一条语句，但是逻辑上要求多条语句，
这时就需要块（复合语句）
*********************************************************************/

void Ex_5_3()
{
    int sum = 0,val = 0;
    while(++val,val <= 10)
    {
        sum += val;
    }
    cout << "Sum of 1 to 10 inclusive is " << sum << endl;
}
/*******************************************************************
Ex_5_4:
(a)迭代字符串s的每个字符，并执行一定的操作
(b)判断是否找到某个元素word，该处存在问题，status作用域不对
应改为：
bool status;
while(status = find(word))...
*********************************************************************/
void Ex_5_5(int grade)
{
    const vector<string> scores = {"F","E","D","C","B","A","A++"};
    string lettergrade;
    if(grade < 60)
        lettergrade = scores[0];
    else
        lettergrade = scores[grade/10-5];
    cout << lettergrade;
}
void Ex_5_6(int grade)
{
    const vector<string> scores = {"F","E","D","C","B","A","A++"};
    string lettergrade;
    lettergrade = (grade < 60 ? scores[0] : scores[grade/10-5]);
    cout << lettergrade;
}
/*******************************************************************
Ex_5_7:
(a)缺少逗号
(b)应使用复合语句块
(c)ival应定义在for之外
(d)应使用“==”
*********************************************************************/

void Ex_5_9()
{
    string str;
    cout << "Input a string: ";
    cin >> str;
    unsigned vowelCnt = 0;
    for(auto i : str)
    {
        switch(i)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            ++vowelCnt;
            break;

        }
    }
    cout << vowelCnt << endl;

}
void Ex_5_10()
{
    string str;
    cout << "Input a string: ";
    cin >> str;

    unsigned aCnt = 0,eCnt = 0,iCnt = 0,oCnt = 0,uCnt = 0;
    for(auto i : str)
    {
        if(isupper(i))
        {
            i = tolower(i);
        }
        switch(i)
        {
        case 'a':aCnt++;break;
        case 'e':eCnt++;break;
        case 'i':iCnt++;break;
        case 'o':oCnt++;break;
        case 'u':uCnt++;break;

        }
    }
    cout << aCnt << eCnt << iCnt << oCnt << uCnt << endl;

}
int main1550()
{
    Ex_5_3();
    Ex_5_5(75);
    Ex_5_6(75);
    Ex_5_9();
    Ex_5_10();
    return 0;
}
