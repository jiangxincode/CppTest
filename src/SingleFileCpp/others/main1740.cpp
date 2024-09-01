#include <iostream>
#include <map>
#include <string>

using namespace std;

void test_4_12()
{
    int line,row; //the line and row of the array
    cout << "Input the size of the array(line row): ";
    cin >> line >> row;
    int **array_source = new int *[line];
    for (int i = 0; i < line; i++) {
        array_source[i] = new int[row];
    }
    int **array_target = new int *[line];
    for (int i = 0; i < line; i++) {
        array_target[i] = new int[row];
    }

    for(int i=0; i<line; i++) //输出数据
    {
        for(int j=0; j<row; j++)
        {
            cin >> array_source[i][j];
        }
    }

    for(int i=0; i<line; i++) //初始化array_target
    {
        for(int j=0; j<row; j++)
        {
            array_target[i][j] = 0;
        }
    }

    cout << endl;

    for(int i=0; i<line; i++) //找到每行最小的那些列
    {
        int min = array_source[i][0];

        for(int j=0; j<row; j++)
        {
            if(array_source[i][j] < min)
            {
                min = array_source[i][j];
            }
        }

        for(int j=0; j<row; j++)
        {
            if(array_source[i][j] == min)
            {
                array_target[i][j]++;
            }
        }
    }

    for(int j=0; j<row; j++) //找到每列最大的那些行
    {
        int max = array_source[0][j];

        for(int i=0; i<line; i++)
        {
            if(array_source[i][j] > max)
            {
                max = array_source[i][j];
            }
        }

        for(int i=0; i<line; i++)
        {
            if(array_source[i][j] == max)
            {
                array_target[i][j]++;
            }
        }
    }

    int exist = 0;

    for(int i=0; i<line; i++)
    {
        for(int j=0; j<row; j++)
        {
            if(array_target[i][j] == 2)
            {
                cout << "(" << i << "," << j << ") ";
                exist = 1;
            }
        }
    }

    if(exist == 0)
    {
        cout << "No data proper!!" << endl;
    }
    for (int i = 0; i < line; i++) {
        delete[] array_source[i];
    }
    delete[] array_source;
    for (int i = 0; i < line; i++) {
        delete[] array_target;
    }
    delete[] array_target;
}

void test_4_14()
{
    string s,t,v;
    string::size_type idx;
    cout << "Input the string s:" << endl;
    cin >> s;
    cout << "Input the string t:" << endl;
    cin >> t;
    cout << "Input the string v:" << endl;
    cin >> v;

    while((idx=s.string::find(t)) != string::npos)
    {
        s=s.string::replace(idx,t.string::length(),v);
    }

    cout << s << endl;
}

void test_4_15()
{
    string str = "ajkfsldksldjfiejagjklaellgjlanvalurekfklaghlejlakjglagklgjlekagej";
    map<char,int> map_char;

    for(auto ch : str)
    {
        ++map_char[ch];
    }

    for(auto ch : map_char)
    {
        cout << ch.first << ": " << ch.second << endl;
    }
}

int main()
{
    return 0;
}

