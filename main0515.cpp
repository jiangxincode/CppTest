/*
��Ϊ��˾2014��У԰��Ƹ������ϻ���������
10��ѧ��������ĩ����������ɺ�A��ʦ��Ҫ���������ߣ�Ҫ�����£�
(1) ��������10�ı�����
(2) ��֤������60%��ѧ������
(3) ������е�ѧ��������60�֣��򼰸���Ϊ60��
���룺����10��������ȡֵ0~100
�������������ߣ�10�ı���
����������61 51 49 30 20 10 70 80 90 99
���������50
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

int main05152() //���ϵĲο�
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
