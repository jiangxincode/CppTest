/*
���ƿƼ�������
���µĴ���ɷ���VC++6.0�������С�
��Ŀ��Ҫ�������TrendMicroSoftUSCNȻ��Ҫ���޸ĳ���ʹ������������Ͻ���� �������£�
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char * argv[])
{
    string strArr1[] = { "Trend", "Micro", "soft"};
    string *p = new string[2];
    p[0] = "US";
    p[1] = "CN";
    for(int i=0;i < sizeof(strArr1)/sizeof(string);i++)
        cout << strArr1[i];
    for(i=0;i < sizeof(p)/sizeof(string);i++)
        cout << p[i];
    cout << endl;
}
*/
#include <iostream>
#include <string>
using namespace std;
int main0537()
{
    string strArr1[]= { "Trend", "Micro", "soft"};
    string *p=new string[2];
    p[0] = "US";
    p[1] = "CN";
    cout << sizeof(strArr1) << endl;
    cout << sizeof(p) << endl;
    cout << sizeof(string) << endl;

    for(size_t i=0; i < sizeof(strArr1)/sizeof(string); i++)
        cout << strArr1[i];

    for(size_t i=0; i < sizeof(p)*2/sizeof(string); i++)
        cout << p[i];

    cout <<endl;
    return 0;
}

/*
����Ҫ��ȷsizeof ���Ǻ�����Ҳ����һԪ��������Ǹ����ƺ궨�������ؼ��֣�
sizeof�������������ڱ���������ǲ�������ģ����Ǳ�������ͣ�
�� int a=8��sizeof��a�����ڱ�������У�������a��ֵ��ʲô��ֻ�Ǳ��滻������ sizeof��int����
���Ϊ4.
���sizeof��a=6������,Ҳ��һ����ת����a�����ͣ�����Ҫע����Ϊa=6�ǲ�������ģ�
����ִ����sizeof��a=6����a��ֵ����6���ǲ���ģ�

��ס���¼������ۣ�
1.unsignedӰ���ֻ�����λbit�����壨�����������ݳ��Ȳ��ᱻ�ı�ġ�
����sizeof(unsigned int) == sizeof(int)��
2.�Զ������͵�sizeofȡֵ��ͬ����������ԭ�Ρ�
��typedef short WORD;sizeof(short) == sizeof(WORD)��
3.�Ժ���ʹ��sizeof���ڱ���׶λᱻ��������ֵ������ȡ�����磺int f1(){return 0;};
cout < <sizeof(f1()) < <endl; // f1()����ֵΪint����˱���Ϊ��int
4.ֻҪ��ָ�룬��С����4���磺cout < <sizeof(string*) < <endl; // 4
5.����Ĵ�С�Ǹ�ά���ĳ˻�*����Ԫ�صĴ�С���磺char a[] = "abcdef ";
int b[20] = {3, 4};
char c[2][3] = { "aa ", "bb "};
cout < <sizeof(a) < <endl; // 7
cout < <sizeof(b) < <endl; // 20*4
cout < <sizeof(c) < <endl; // 6
����a�Ĵ�С�ڶ���ʱδָ��������ʱ��������Ŀռ��ǰ��ճ�ʼ����ֵȷ���ģ�
Ҳ����7��������\0���ġ�
6.�ַ�����sizeof��strlen��������˵����
char a[] = "abcdef ";
char b[20] = "abcdef ";
string s = "abcdef ";
cout < <strlen(a) < <endl; // 6���ַ�������
cout < <sizeof(a) < <endl; // 7���ַ�������
cout < <strlen(b) < <endl; // 6���ַ�������
cout < <sizeof(b) < <endl; // 20���ַ�������
cout < <sizeof(s) < <endl; // 16, ���ﲻ�����ַ����ĳ��ȣ�����string��Ĵ�С
cout < <strlen(s) < <endl; // ����s����һ���ַ�ָ�롣
a[1] = '\0 ';
cout < <strlen(a) < <endl; // 1
cout < <sizeof(a) < <endl; // 7��sizeof�Ǻ㶨��

�����������ͽ���Ĳ���ˣ�sizeof(string)=16��yi-0220��˵��
�����Ĵ��ǣ�for(i=0;i <sizeof(p)/sizeof(string);i++)
��Ϊfor(i=0;i <sizeof(p)*2/sizeof(string);i++) ��Ҳ�ǲ��Եģ�sizeof��p)ֻ��ָ���С Ϊ4�� Ҫ���������pָ������ĳ�Ա������Ӧ��Ϊsizeof(*p)*8/sizeof(string)��Ϊʲô��
ָ��pָ�����飬��*p����ָ�������еĳ�Ա�ˣ���Ա��������ʲô��string�ͣ�ok��ôsizeof(*p)Ϊ16������2������������Ĵ�С
*/

