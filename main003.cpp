#include <iostream>
#include <string>
/*
����һ��query��һ��text������Сд��ĸ��ɡ�
Ҫ����text���ҳ���ͬ����˳������������query�е��������ĸ���еĳ��ȡ�
���磬 queryΪ��acbac����textΪ��acaccbabb����
��ôtext�еġ�cba��Ϊ�������������query�е���ĸ���У�
��ˣ����ؽ��Ӧ��Ϊ�䳤��3��
��ע�����Ч�ʡ�
2015 ����Ͱ� �����з�����ʦ ���߱���
*/
using namespace std;

int main003()
{
    string text,query;
    cout << "Input text: " << endl;
    cin >> text;
    cout << "Input query: " << endl;
    cin >> query;
    string::size_type len = 0;
    for(string::size_type i=0; i<query.length(); i++)
    {
        for(string::size_type j=query.length()-1; j>i; j--)
        {
            string temp = query.substr(i,j);
            if(text.find(temp) != string::npos)
            {
                if((j-i)>len)
                {
                    len = j - i + 1; //i��jλ��֮�й���(j-i+1)��Ԫ��
                }
            }
        }
    }
    cout << len;
    return 0;
}
