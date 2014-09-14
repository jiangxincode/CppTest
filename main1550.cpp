#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*******************************************************************
Ex_5_1:
��������ֻ����һ���ֺŵ���䡣
����ڳ����ĳ���ط����﷨��Ҫ����һ����䣬�����߼��ϲ���Ҫ��
��ʱ����Ҫһ������䡣
Ex_5_2:
������ɻ����Ű�Χ�ĸ�����䡣
����ڳ����ĳ���ط����﷨��Ҫ����һ����䣬�����߼���Ҫ�������䣬
��ʱ����Ҫ�飨������䣩
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
(a)�����ַ���s��ÿ���ַ�����ִ��һ���Ĳ���
(b)�ж��Ƿ��ҵ�ĳ��Ԫ��word���ô��������⣬status�����򲻶�
Ӧ��Ϊ��
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
(a)ȱ�ٶ���
(b)Ӧʹ�ø�������
(c)ivalӦ������for֮��
(d)Ӧʹ�á�==��
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
