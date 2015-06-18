﻿#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <climits>
#include <cstdio>

using namespace std;


void test_4_12_a()
{
    int line,row; //the lines and rows of the array
    int flag_end = 10000; //a flag for the end of loop
    int ch; //a temp char for fflushing the stdin
    int flag_exist = 0; //if a result exists, then the variable is 1
    cout << "Input the size of the array(LINE ROW):" << endl;
    cin >> line >> row;

    while((ch=getchar()!='\n') && (ch!=EOF)); //fflush the stdin

    int A[line][row]; //storge the origin array
    int B[line+1][row+1]; //storge the position of every line,a position for the flag_end
    int C[line+1][row+1]; //storge the position of every row,a position for the flag_end

    for(int i=0; i<line; i++) //get the array data from the keybord
    {
        cout<<"Input data of the line "<<i+1<<" ("<<row<<" integers)"<<endl;

        for(int j=0; j<row; j++)
        {
            cin >> A[i][j];
        }

        while((ch=getchar()!='\n') && (ch!=EOF)); //fflush the stdin
    }

    cout << endl;
    cout << "Check your input:" << endl;

    for(int i=0; i<line; i++)
    {
        for(int j=0; j<row; j++)
        {
            cout << A[i][j] << "\t";
        }

        cout << endl;
    }

    for(int i=0; i<line; i++) //get the min position of every line
    {
        int min=A[i][0];
        B[i][0]=0;
        int m=0;

        for(int j=1; j<row; j++)
        {
            if(A[i][j]<min)
            {
                min=A[i][j];
                B[i][0] = j;
                m=0;
            }
            else if(A[i][j]==min)
            {
                B[i][++m] = j;
            }
        }

        B[i][++m] = flag_end;
    }

    for(int j=0; j<row; j++) //get the max position of every row
    {
        int max=A[0][j];
        C[j][0]=0;
        int n=0;

        for(int i=1; i<line; i++)
        {
            if(A[i][j]>max)
            {
                max=A[i][j];
                C[j][0] = i;
                n=0;
            }
            else if(A[i][j]==max)
            {
                C[j][++n] = i;
            }
        }

        C[j][++n] = flag_end;
    }

    cout << endl;
    cout << "The smallest position of every line:" <<endl;

    for(int i=0; i<line; i++)
    {
        for(int j=0; B[i][j]!=flag_end; j++)
        {
            cout << B[i][j] << "\t";
        }

        cout << endl;
    }

    cout << endl;
    cout << "The biggest position of every row:" <<endl;

    for(int j=0; j<row; j++)
    {
        for(int i=0; C[j][i]!=flag_end; i++)
        {
            cout << C[j][i] << "\t";
        }

        cout << endl;
    }

    for(int i=0; i<line; i++)
    {
        for(int m=0; B[i][m]!=flag_end; m++)
        {
            for(int n=0; C[B[i][m]][n]!=flag_end; n++)
            {
                if(C[B[i][m]][n]==i)
                {
                    cout << "(" << i << "," << B[i][m] << ")" << "\t";
                    flag_exist = 1;
                }
            }
        }
    }

    if(flag_exist == 0)
    {
        cout << "No pairs meet the requirement!";
    }

    cout << endl;
}
void test_4_12_b()
{
    int line,row; //the line and row of the array
    cout << "Input the size of the array(line row): ";
    cin >> line >> row;
    int array_source[line][row];
    int array_target[line][row];

    for(int i=0; i<line; i++) //输出数据
    {
        cout << "Input the data of line " << (i+1) <<": ";

        for(int j=0; j<row; j++)
        {
            cin >> array_source[i][j];
        }
    }

    cout << endl;

    for(int i=0; i<line; i++) //输出
    {
        for(int j=0; j<row; j++)
        {
            cout << array_source[i][j] << " ";
        }

        cout << endl;
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

    for(int i=0; i<line; i++) //array_target
    {
        for(int j=0; j<row; j++)
        {
            cout << array_target[i][j] << " ";
        }

        cout << endl;
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
}

void test_4_12_c()
{
    int line,row; //the line and row of the array
    cout << "Input the size of the array(line row): ";
    cin >> line >> row;
    int array_source[line][row];
    int array_target[line][row];
    int array_line[line];
    int array_row[row];

    for(int i=0; i<line; i++) //输出数据
    {
        cout << "Input the data of line " << (i+1) <<": ";

        for(int j=0; j<row; j++)
        {
            cin >> array_source[i][j];
        }
    }

    cout << endl;

    for(int i=0; i<line; i++) //输出
    {
        for(int j=0; j<row; j++)
        {
            cout << array_source[i][j] << " ";
        }

        cout << endl;
    }

    for(int i=0; i<line; i++) //初始化array_target
    {
        for(int j=0; j<row; j++)
        {
            array_target[i][j] = 0;
        }
    }

    for(int i=0; i<line; i++) //初始化array_line
    {
        array_line[i] = 0;
    }

    for(int j=0; j<row; j++) //初始化array_row
    {
        array_row[j] = 0;
    }

    for(int i=0; i<line; i++) //找到每行最小的那些列
    {
        int min = array_source[i][0];
        int m = 1;

        for(int j=0; j<row; j++)
        {
            if(array_source[i][j] < min)
            {
                min = array_source[i][j];
                array_target[i][j] += (++m);
            }
            else if(array_source[i][j] == min)
            {
                array_target[i][j] += m;
            }

            array_line[i] = m;
        }
    }

    for(int j=0; j<row; j++) //找到每列最大的那些行
    {
        int max = array_source[0][j];
        int n = 1;

        for(int i=0; i<line; i++)
        {
            if(array_source[i][j] > max)
            {
                max = array_source[i][j];
                array_target[i][j] += (++n);
            }
            else if(array_source[i][j] == max)
            {
                array_target[i][j] += n;
            }

            array_row[j] = n;
        }
    }

    for(int i=0; i<line; i++) //array_target
    {
        for(int j=0; j<row; j++)
        {
            cout << array_target[i][j] << " ";
        }

        cout << endl;
    }

    int exist = 0;

    for(int i=0; i<line; i++)
    {
        for(int j=0; j<row; j++)
        {
            if(array_target[i][j] == (array_line[i] + array_row[j]))
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
}

/*
二维数组的局部鞍点定义如下：
对任意一个二维数组中的元素，若该元素的值比其上下2个相邻元素的值都小
并且比其左右2个相邻元素的值都大，则称该元素是一个局部鞍点。
位于矩阵拐角和边界的元素分别只有2个和3个相邻元素。
函数localmin的形参a指向输入数组，b指向输出数组。
该函数的功能是找出输入数组中所有局部鞍点，
若输入数组的某个元素是局部鞍点，则将输出数组的相同位置处的元素置1；否则置0。
*/

void localmax(int a[6][6],int b[6][6])
{
    int i,j,k,m;

    for(i=1; i<=4; i++)
        for(j=1; j<=4; j++)
        {
            b[i][j]=1;

            for(k=-1; k<=1; k++)
                for(m=-1; m<=1; m++)
                {
                    if((k==-1||k==1) && (m==-1||m==1)) continue;

                    if((k==0&&a[i][j]>a[i+m][j+k])||(m==0&&a[i][j]<a[i+m][j+k]))
                        b[i][j]=0;
                }
        }
}
int test_4_12_d()
{
    int b[6][6];
    int i,j,a[6][6]= {{0},{0,6,9,2,4},{0,3,6,8,5},{0,2,1,4,1},{0,6,2,9,4}};

    for(j=0; j<6; j++)
    {
        a[0][j]=INT_MAX;
        a[j][0]=INT_MIN;
        a[5][j]=INT_MAX;
        a[j][5]=INT_MIN;
    }

    localmax(a,b);

    for(i=1; i<=4; i++)
    {
        for(j=1; j<=4; j++)
        {
            cout << setw(8) << a[i][j];
        }

        cout << endl;
    }

    for(i=1; i<=4; i++)
    {
        for(j=1; j<=4; j++)
        {
            cout << setw(8) << b[i][j];
        }

        cout << endl;
    }

    return 0;
}


/*找出一个二维数组中的所有鞍点并输出。
  若一个数组元素的值是所在行的最大值，同时是所在列的最小值，该数组元素就是鞍点。
  一个二维数组中可能没有鞍点，也可能有多个鞍点。
  编程要求： 编写main函数。声明一个二维数组a并用测试矩阵初始化，在数组a中查找鞍点,输出找到的所有鞍点位置。
  测试矩阵:
       1    2    3    4
       5    6    7    8
       9   10  11   12
       13 14  15   16
    输出结果：
      The saddle point is：a[0][3]
*/

int test_4_12_e()
{
    int k,t=0;
    int a[4][4]= {{1,2,3,4,},{5,6,7,8},{9,10,11,12},{13,14,15,16}};

    for(int i=0; i<4; i++)
    {
        int max=a[i][0];
        int maxj;
        int j=0;

        for(j=0; j<4; j++)
            if(a[i][j]>max)
            {
                max=a[i][j];
                maxj=j;
            }

        for(k=0; k<4; k++)
            if(a[k][maxj]<max)
                break;

        if(k>=4)
        {
            cout << i << " " << maxj << endl;
            t=1;
        }
    }

    if(t==0) cout << "There is no saddle point!" << endl;

    return 0;
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

int main1740()
{
    return 0;
}

