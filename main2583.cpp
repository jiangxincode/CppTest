/*
��֪һ��Ӣ�����ĵļ��ܷ���Ϊ����ԭ���е�ÿ����ĸ���ֱ�����ĸ���и���ĸ֮��ĵ�5����ĸ�滻
���磺
��I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME��
������Ϊ
��N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ��
��д���ܺ���
*/

#include <iostream>
#include <string>

using namespace std;

int main2583()
{
    string str_src("N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ");

    for(auto &ch : str_src)
    {
        if(islower(ch))
        {
            auto diff = ch - 'a' - 5;
            ch = (diff>0)?(ch-5):(ch-5+26);
        }
        else if(isupper(ch))
        {
            auto diff = ch - 'A' - 5;
            ch = (diff>0)?(ch-5):(ch-5+26);
        }
    }

    cout << str_src << endl;
    return 0;
}
