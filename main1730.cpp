#include <iostream>
#include <stack>
#include <string>

#include <cstring>
#include <cstdio>

using namespace std;

/*
试编写一个算法，检查一个程序中的花括号/方括号和园括号是否配对，
若能够全部配对则返回1,否则返回0.
*/
bool isMatch(string str)
{
    stack<char> sta;
    string mark = "([{)]}";

    for(unsigned i=0; i<str.length(); i++)
    {
        char temp = str[i];
        string::size_type pos = mark.find(temp);

        if((pos>=0) && (pos<3)) //([{
        {
            sta.push(temp);
            continue;
        }
        else if((pos >= 3) && (pos < 6)) //)]}
        {
            if(sta.empty() || (sta.top()!=mark[pos-3]))
            {
                return false;
            }
            else
            {
                sta.pop();
                continue;
            }
        }
    }

    if(sta.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main17300()
{
    string expression;
    cin >> expression;
    cout << isMatch(expression);
    return 0;
}

/*
百度2014校园招聘-研发工程师笔试题
给定一个如下格式的字符串(1,(2,3),(4,(5,6),7))
括号内的元素可以是数字，也可以是另一个括号，
请实现一个算法消除嵌套的括号，
比如把上面的表达式变成：(1,2,3,4,5,6,7)
如果表达式有误请报错。(15分)
*/
int main17304()
{
    string str = "(1,(2,3),(4,(5,6),7))";
    string result = "";
    stack<char> sta;

    for(string::iterator it=str.begin(); it!=str.end(); ++it)
    {
        char temp = *it;

        if((temp == '(') && sta.empty())
        {
            result += temp;
            sta.push(temp);
        }
        else if((temp == '(') && !sta.empty())
        {
            sta.push(temp);
        }
        else if((temp == ')') && sta.empty())
        {
            cerr << "Error!" << endl;
            exit(1);
        }
        else if((temp == ')') && !sta.empty())
        {
            sta.pop();
        }
        else
        {
            result += temp;
        }
    }

    result += ')';
    cout << result << endl;
    return 0;
}

/*
八皇后问题，是一个古老而著名的问题，是回溯算法的典型案例。
该问题是国际西洋棋棋手马克斯·贝瑟尔于1848年提出：
在8X8格的国际象棋上摆放八个皇后，使其不能互相攻击，
即任意两个皇后都不能处于同一行、同一列或同一斜线上，问有多少种摆法。
*/
static const int N = 100;
class Queen
{
public:
    Queen()
    {
        count=0;
    }
    void Print(int n); //输出皇后的排列，打出的数字为每个皇后的坐标
    int Check(int i,int k); //判断位置是否符合要求
    void Queens(int k,int n); //递归调用
    int getCount()
    {
        return count; //计数
    }
private:
    int q[N]; //记录皇后的位置
    int count;
};

//计算出皇后的排列，k是当前皇后数量，n是数量上限
void Queen::Queens(int k,int n)
{
    if(k>n) //如果达到要求的数量输出皇后排列
    {
        count ++;
        Print(n);
    }
    else //否则在适当的位置添加一个新皇后
    {
        for(int j=1; j<=n; j++)
            if(Check(k,j)) //判断第k个皇后放置在第j列是否满足条件
            {
                q[k]=j; //记录第k个皇后在第几列
                Queens(k+1,n); //放置下一行的皇后
            }
    }
}
void Queen::Print(int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cout << (j==q[i]?"Q ":"* ");
        }

        cout<<endl;
    }

    cout<<endl;
}
int Queen::Check(int k,int j)
{
    for(int i=1; i<k; i++)
    {
        //q[i]==j检验第i个皇后是否在第j列
        //abs(i-k)==abs(q[i]-j)检验第i个皇后与第k个皇后位置是否在一条斜线上
        //检验是否在一条斜线的方法是判断行与列的差值相同
        if((q[i]==j) || abs(i-k)==abs(q[i]-j))
            return 0;
    }

    return 1;
}

void test_3_17()
{
    Queen Q;
    int n;
    cout << "请输入Queen的数目(n>0):" << endl;
    cin >> n;
    cout << "Queen可能的位置坐标:" << endl;
    Q.Queens(1,n);
    cout << "共有 " << Q.getCount() << " 种方法放置Queen"<<endl;
}

/*
试编写一个算法，求解最大公因数问题：
在求两个正整数m和n的最大公因数常常使用辗转相除法，反复计算直到余数为零为止。
*/
int GCD(int x,int y)
{
    int temp;

    if(x < y)
    {
        temp = x;
        x = y;
        y = temp;
    }

    if(y == 0)
        return x;
    else
    {
        temp = x % y;
        return GCD(y,temp);
    }
}
void test_3_21()
{
    int num_1,num_2;
    int result;
    puts("Input two integer:");
    cin >> num_1 >> num_2;
    result = GCD(num_1,num_2);
    cout << result;
}

/*
背包类似问题合集
*/

/*
1.典型背包问题
*/
static const int MAXNUM = 100;

bool KNAP(int s,int n, int w[])
{
    if(s == 0)
    {
        return true;
    }
    else if(s < 0)
    {
        return false;
    }
    else if(s > 0 && n < 1)
    {
        return false;
    }

    while(s > 0 && n >= 1)
    {
        bool flag = KNAP(s,n-1,w);

        if(flag)
        {
            return true;
        }

        flag =  KNAP((s-w[n]),n-1,w);

        if(flag)
        {
            cout << n << " ";
            return true;
        }

        n--;
    }

    return false;
}

int main17301()
{
    int n = 0,s=0;
    bool flag = false;
    int w[MAXNUM];
    cout << "Input the weight of the bag can hold:" <<endl;
    cin >> s;
    cout << "Input the number of the objects" <<endl;
    cin >> n;

    for(int i=1; i<=n; i++)
    {
        cout << "The weight of the object " << i <<endl;
        cin >> w[i];
    }

    flag = KNAP(s,n,w);

    if(!flag)
    {
        cout << "This bag question has no solution" << endl;
    }

    cout << endl;
    return flag;
}

/*
背包问题:
第一行输入给定重量以及物品数量
第二行输入每个物品的质量
如果包含该物品则对应输出1，否则对应输出0
example:
input:20 5
input:1 3 5 7 8
output:0 0 1 1 1
*/
int find(int weight,int num,int *object,int *result)
{
    if(weight == 0)
    {
        return 1;
    }
    else if(weight < 0 || num < 0)
    {
        return 0;
    }
    else if(weight > 0 && num < 1)
    {
        return 0;
    }
    else
    {
        if(find(weight-object[num-1],num-1,object,result))
        {
            result[num-1] = 1;
            return 1;
        }
    }

    return find(weight,num-1,object,result);
}


int main17302()
{
    int weight,num;
    cin >> weight >> num;
    int *object = new int[num]; //动态数组一定要释放
    int *result = new int[num];

    for(int i=0; i<num; i++)
    {
        result[i] = 0;
    }

    for(int i=0; i<num; i++)
    {
        cin >> *(object+i);
    }

    if(find(weight,num,object,result))
    {
        for(int i=0; i<num; i++)
        {
            cout << result[i] << " ";
        }
    }
    else
    {
        cout << "No" << endl;
    }

    delete []object;
    delete []result;
    return 0;
}

/*
给定一些硬币，求给定金额下，最少硬币的组合
*/

int main17303()
{
    int group;
    cout << "How many groups of the coins: ";
    cin >> group;
    int *coin = new int[group];

    for(int i=0; i<group; i++)
    {
        cin >> coin[i];
    }

    for(int i=0; i<group; i++)
    {
        cout << coin[i] << " ";
    }

    cout << endl;
    delete []coin;
    return 0;
}
int main1730()
{
    main17304();
    return 0;
}
