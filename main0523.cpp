/*
������ˮ
ĳ������7������:������ˮ��Ϊ�˺����������ܳ�ͻ����Ҫ�滮ÿ�������ˮ�ĺ��С�

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

ע�ͣ�
�����еĵ�i�д����i������һ�����п���ʱ�������������һ������
�����һ��Ϊ���з�������Ŀ���Ժ�ÿ�����һ�ַ�����ÿһ�ַ����������һ������ĺ��б��
*/

#include<iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct st
{
    int spare[8]; //�洢���еĿ���ʱ�䣬spare[i]=0��ʾ����iû�п��У�spare[i]=1��ʾ����i����,����spare[0]����
    int flag; //���ڱ�Ǻ��б������Ƿ��Ѿ���������flag��0��ʾû����ˮ��flag��1��ʾ�Ѿ�����ˮ
} monk[8];

int x[8]; //ÿ�찲�ŵĺ��б�ţ�����x[0]����
int sum=0; //sum����ͳ�ƹ��ж����ַ���
vector<vector<int>> result;
vector<int> temp;
//�������ܣ���˷����n������7��Ľ⣨����n��7��ֱ����ĸ�����
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
            if(monk[j].flag==0&&monk[j].spare[n]==1) //�жϺ���j�Ƿ��Ѿ�����ˮ����������n�Ƿ��п�
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
        //��ʼ�����еĿ���ʱ��,��ʼ��ʱ����ȫ��û����ˮ��flag��Ϊ0
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
            cin >> data[i][j]; //��i�����е�j���Ƿ����
        }
    }
	//����ȫ���н��а���������������ȫ���к���
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
