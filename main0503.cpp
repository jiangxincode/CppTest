#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

//����cin cin.getline cin.get getline gets getchar ���÷�ʵ��
int main0503()
{
//1��cin>>
    //method one�� Ҳ������õķ��� ����һ������
    cout << "Test cin>> �÷�1��" << endl;
    int a,b;
    cout << "input two integer:" << endl;
    cin >> a >> b;
    cout << "SUM =" << a + b << "\n" << endl;
    //method two������һ���ַ������������ո� �س� Tab��������
    cout << "Test cin>>�÷�2��" << endl;
    char array[10];
    cout << "input a char array:" << endl;
    cin >> array;
    cout << array << "\n" << endl;
//2��cin.get()
    //one cin.get(�ַ�������) �������������ַ�
    cout << "Test cin.get(�ַ�������)��" << endl;
    char ch;
    cout << "Input a char:" << endl;
    cin.get(); //��֮ǰ����Ļس�������ȥ
    ch = cin.get(); //or cin.get(ch);
    cout << ch << "\n" << endl;
    //two cin.get(�ַ����飬���յ��ַ���) ��������һ���ַ������Խ��տո�
    cout << "Test cin.get(�ַ����飬���յ��ַ���):" << endl;
    char array1[20];
    cout << "Input a char array:" << endl;
    ch = cin.get(); //��֮ǰ����Ļس�������ȥ
    cin.get(array1,10);
    cout << array1 << "\n" << endl;
    //ע:cin.get(�޲���)��Ҫ���������������в���Ҫ���ַ� ���������س�
    //�Ӷ��ֲ���cin.get(�ַ����飬���յ��ַ���)�Ĳ���
//3��cin.getline(cin,str)  ����һ���ַ��� ���Խ��տո�
    cout << "Test cin.getline() ���÷���" << endl;
    char array2[20];
    cout << "Input a char array:" << endl;
    ch = cin.get(); //��֮ǰ����Ļس�������ȥ
    cin.getline(array2,20);
    cout << array2 << "\n" << endl;
    //ʵ����cin.get(�ַ����飬���յ��ַ���) ��cin.getline(�ַ����飬���յ��ַ���)
    //����������cin.getline(�ַ����飬�����ַ����������ַ�) ����������Ĭ����'\0'
    //��ά������Ҳ�����õ�cin.getline(�ַ����飬���յ��ַ���)���÷�
    cout << "cin.get(�ַ����飬���յ��ַ���) is used in multidimensional array:" << endl;
    char array3[3][10];

    for(int i = 0; i < 3; i ++)
    {
        cout << "�������" << i+1 << "�е��ַ�����" << endl;
        cin.getline(array3[i],10);
    }

    for(int j = 0; j < 3; j ++)
    {
        cout << "��" << j+1 << "�У�" << array3[j] << endl;
    }

//4��getline(cin,str)���÷� ����һ�����԰����ո���ַ���(�����string���͵�) ��Ҫ����ͷ�ļ�#include <string>
    //getline(cin,str)��string������i/o��
    cout << "Test getline(cin,str):" << endl;
    string str;
    cout << "Input a string:" << endl;
    //ch = cin.get(); //��֮ǰ����Ļس�������ȥ
    getline(cin,str);
    cout << str << "\n" << endl;
//5��gets(char *) ����һ�����԰����ո���ַ��� ��Ҫ����ͷ�ļ�#include <string>
    cout << "Test gets(char *)���÷�" << endl;
    char array4[20];
    cout << "input a char array:" << endl;
    ch = cin.get(); //��֮ǰ����Ļس�������ȥ
    gets(array4);
    //The gets function reads a line from the standard input stream stdin and stores it in buffer.
    //The line consists of all characters up to and including the first newline character ('\n').
    //gets then replaces the newline character with a null character ('\0') before returning the line
    cout << array4 << "\n" << endl;
    //gets(char *)Ҳ�������ڶ�ά�������� ��cin.getline()�÷�����
//6��getchar(�޲���) ����һ���ַ� ��Ҫ����ͷ�ļ�#include <string>
    cout << "Test getchar(�޲���)���÷���" << endl;
    char ch1;
    cout << "input a char:" << endl;
    ch1 = getchar(); // ����д��getchar(ch1);
    cout << ch1 << "\n" << endl;
    //getchar()��C�ĺ��� C++�Ǽ���C ����Ҳ����ʹ�� ���������û�����
    return 0;
}
