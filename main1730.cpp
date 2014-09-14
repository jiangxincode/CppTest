#include <iostream>
#include <stack>
#include <string>

#include <cstring>
#include <cstdio>

using namespace std;

/*
�Ա�дһ���㷨�����һ�������еĻ�����/�����ź�԰�����Ƿ���ԣ�
���ܹ�ȫ������򷵻�1,���򷵻�0.
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

int test_3_13()
{
    string expression;
    cin >> expression;
    cout << isMatch(expression);
    return 0;
}

/*
�˻ʺ����⣬��һ�����϶����������⣬�ǻ����㷨�ĵ��Ͱ�����
�������ǹ����������������˹����ɪ����1848�������
��8X8��Ĺ��������ϰڷŰ˸��ʺ�ʹ�䲻�ܻ��๥����
�����������ʺ󶼲��ܴ���ͬһ�С�ͬһ�л�ͬһб���ϣ����ж����ְڷ���
*/
#define N 100
class Queen
{
public:
    Queen()
    {
        count=0;
    }
    void Print(int n); //����ʺ�����У����������Ϊÿ���ʺ������
    int Check(int i,int k); //�ж�λ���Ƿ����Ҫ��
    void Queens(int k,int n); //�ݹ����
    int getCount()
    {
        return count; //����
    }
private:
    int q[N]; //��¼�ʺ��λ��
    int count;
};

//������ʺ�����У�k�ǵ�ǰ�ʺ�������n����������
void Queen::Queens(int k,int n)
{
    if(k>n) //����ﵽҪ�����������ʺ�����
    {
        count ++;
        Print(n);
    }
    else //�������ʵ���λ�����һ���»ʺ�
    {
        for(int j=1; j<=n; j++)
            if(Check(k,j)) //�жϵ�k���ʺ�����ڵ�j���Ƿ���������
            {
                q[k]=j; //��¼��k���ʺ��ڵڼ���
                Queens(k+1,n); //������һ�еĻʺ�
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
        //q[i]==j�����i���ʺ��Ƿ��ڵ�j��
        //abs(i-k)==abs(q[i]-j)�����i���ʺ����k���ʺ�λ���Ƿ���һ��б����
        //�����Ƿ���һ��б�ߵķ������ж������еĲ�ֵ��ͬ
        if((q[i]==j) || abs(i-k)==abs(q[i]-j))
            return 0;
    }
    return 1;
}

void test_3_17()
{
    Queen Q;
    int n;
    cout << "������Queen����Ŀ(n>0):" << endl;
    cin >> n;
    cout << "Queen���ܵ�λ������:" << endl;
    Q.Queens(1,n);
    cout << "���� " << Q.getCount() << " �ַ�������Queen"<<endl;
}

/*
�Ա�дһ���㷨���������������⣺
��������������m��n�������������ʹ��շת���������������ֱ������Ϊ��Ϊֹ��
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

#define MAXNUM 100
int w[MAXNUM];
bool KNAP(int s,int n)
{
    bool flag = false;

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
        flag = KNAP(s,n-1);

        if(flag)
        {
            return true;
        }

        flag =  KNAP((s-w[n]),n-1);

        if(flag)
        {
            cout << n << " ";
            return true;
        }

        n--;
    }

    return false;
}

int test_3_18()
{
    int n = 0,s=0;
    bool flag = false;
    cout << "Input the weight of the bag can hold:" <<endl;
    cin >> s;
    cout << "Input the number of the objects" <<endl;
    cin >> n;

    for(int i=1; i<=n; i++)
    {
        cout << "The weight of the object " << i <<endl;
        cin >> w[i];
    }

    flag = KNAP(s,n);

    if(!flag)
    {
        cout << "This bag question has no solution" << endl;
    }

    cout << endl;
    return flag;
}

/*
��������:
��һ��������������Լ���Ʒ����
�ڶ�������ÿ����Ʒ������
�����������Ʒ���Ӧ���1�������Ӧ���0
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
int test_3_18_b()
{
    int weight,num;
    scanf("%d %d",&weight,&num);
    int *object = new int[num]; //��̬����һ��Ҫ�ͷ�
    int *result = new int[num];

    for(int i=0; i<num; i++)
    {
        result[i] = 0;
    }

    for(int i=0; i<num; i++)
    {
        scanf("%d",object+i);
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

int main1730()
{
    test_3_17();
    return 0;
}
