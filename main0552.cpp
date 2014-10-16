/**
�ļ�����һ��������Ҫ��������������һ���ļ���
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Order(vector<int>& data) //bubble sort
{
    int count = data.size() ;
    int tag = false ; // �����Ƿ���Ҫ����ð�ݵı�־λ

    for(int i = 0 ; i < count ; i++)
    {
        for(int j = 0 ; j < count - i - 1 ; j++)
        {
            if(data[j] > data[j+1])
            {
                tag = true ;
                int temp = data[j] ;
                data[j] = data[j+1] ;
                data[j+1] = temp ;
            }
        }

        if(!tag)
            break ;
    }
}

void main0552(void)
{
    vector<int>data;
    ifstream in("c:\\data.txt");

    if(!in)
    {
        cout<<"file error!";
        exit(1);
    }

    int temp;

    while(!in.eof())
    {
        in>>temp;
        data.push_back(temp);
    }

    in.close(); //�ر������ļ���
    Order(data);
    ofstream out("c:\\result.txt");

    if(!out)
    {
        cout<<"file error!";
        exit(1);
    }

    for(vector<int>::size_type i = 0 ; i < data.size() ; i++)
        out<<data[i]<<" ";

    out.close(); //�ر�����ļ���
}

