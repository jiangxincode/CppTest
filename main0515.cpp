/*
华为公司2014届校园招聘软件类上机考试样题
10个学生考完期末考试评卷完成后，A老师需要划出及格线，要求如下：
(1) 及格线是10的倍数；
(2) 保证至少有60%的学生及格；
(3) 如果所有的学生都高于60分，则及格线为60分
输入：输入10个整数，取值0~100
输出：输出及格线，10的倍数
输入样例：61 51 49 30 20 10 70 80 90 99
输出样例：50
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main05151()
{
    int temp;
    vector<int> vec;
    for(int i=0;i<10;i++)
    {
        cin >> temp;
        vec.push_back(temp);
    }
    sort(vec.begin(),vec.end());

    if(*vec.begin() > 60)
    {
        cout << 60;
        return 0;
    }
    for(int i=100;i>0;i-=10)
    {
        if(*(vec.begin()+4) > i)
        {
            cout << i;
            return 0;
        }
    }
    return 0;
}

int main05152() //网上的参考
{
	int i = 0,grade=0,n=0,j=0,k=0;
	double score[10];
	for (i = 0; i < 10; i++)
		cin >> score[i];

	for (n =10; ; n--)
	{
		grade = n * 10;
		for (i = 0; i < 10; i++)
		{
			if (score[i] >= grade)
				j= j+1;
		}
		if (j >= 6)
			break;
		j = 0;
	}
	for (i = 0; i < 10; i++)
	{
		if (score[i]>60)
			k = k + 1;
	}
	if (k == 10)
		grade = 60;
	cout << grade;
	return 0;
}

int main0515()
{
    main05152();
    return 0;
}
