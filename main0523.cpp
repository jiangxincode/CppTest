/*
和尚挑水
某寺庙里7个和尚:轮流挑水，为了和其他任务不能冲突，需要规划每天进行挑水的和尚。

input:
0 1 0 1 0 0 0
1 0 0 0 0 1 0
0 0 1 0 0 0 1
0 0 0 0 1 0 0
1 0 0 1 0 1 0
0 1 0 0 1 0 0
0 0 1 0 0 1 1
output:
4
2 6 3 1 4 5 7
2 6 7 1 4 5 3
5 6 3 1 4 2 7
5 6 7 1 4 2 3

注释：
输入中的第i行代表第i个和尚一周内有空闲时间的天数，从周一到周日
输出第一行为可行方案的数目，以后每行输出一种方案，每一种方案代表从周一到周五的和尚编号
*/

#include<iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct st
{
    int spare[8]; //存储和尚的空闲时间，spare[i]=0表示星期i没有空闲，spare[i]=1表示星期i空闲,其中spare[0]不用
    int flag; //用于标记和尚本周内是否已经工作过，flag＝0表示没挑过水，flag＝1表示已经挑过水
} monk[8];

int x[8]; //每天安排的和尚编号，其中x[0]弃用
int sum=0; //sum用于统计共有多少种方案
vector<vector<int>> result;
vector<int> temp;
//函数功能：回朔求解第n天至第7天的解（即第n～7天分别安排哪个和尚
void backtrack(int n)
{
    //int j;
    if(n>7)
    {
        sum++;
        temp.clear();
        for(int j=1; j<=7; j++)
        {
            temp.push_back(x[j]);
        }
        result.push_back(temp);
    }
    else
    {
        for(int j=1; j<=7; j++)
        {
            x[n]=j;
            if(monk[j].flag==0&&monk[j].spare[n]==1) //判断和尚j是否已经挑过水及和尚星期n是否有空
            {
                monk[j].flag=1;
                backtrack(n+1);
                monk[j].flag=0; //important
            }
        }
    }
}


int main05231()
{
    for(int i=1; i<=7; i++)
    {
        //初始化和尚的空闲时间,初始化时和尚全部没挑过水即flag都为0
        for(int j=1; j<=7; j++)
        {
            cin >> monk[i].spare[j];
        }
        monk[i].flag=0;
    }

    backtrack(1);
    cout << sum << endl;
    vector<vector<int>>::iterator it1;
    vector<int>::iterator it2;
    for(it1=result.begin();it1!=result.end();it1++)
    {
        temp = *it1;
        for(it2=temp.begin();it2!=temp.end();it2++)
        {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}

int main05232()
{
	int data[8][8];
	int sum = 0;
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=7; j++)
        {
            cin >> data[i][j]; //第i个和尚第j天是否空闲
        }
    }
	//利用全排列进行包里搜索，下面是全排列函数
	string ooo="1234567";
	vector<string> voo;
	sort(ooo.begin(),ooo.end());
	while(next_permutation(ooo.begin(),ooo.end()))
	{
		for(int i=1;i<=7;i++)
		{
			if((data[ooo[i-1]-'0'][i]) != 1)
				break;
			if(i==7)
            {
                voo.push_back(ooo);
                sum ++;
            }
		}
	}
	cout << sum << endl;
	for(vector<string>::iterator it1=voo.begin();it1!=voo.end();it1++)
    {
        string temp = *it1;
        for(string::iterator it2=temp.begin();it2!=temp.end();it2++)
        {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}
int main0523()
{
    main05232();
    return 0;
}
