#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main2572()
{
	int line,row; //the lines and rows of the array
	int flag_end = 10000; //a flag for the end of loop
	char ch; //a temp char for fflushing the stdin
	int min,max; //storge the min and max value of the array
	int flag_exist = 0; //if there has a result the variable is 1

	cout << "Input the size of the array(LINE ROW):" << endl;
	cin >> line >> row;
	while((ch=getchar()!='\n') && (ch!=EOF)); //fflush the stdin

	int A[line][row]; //storge the origin array
	int B[line+1][row+1]; //storge the position of every line,a position for the flag_end
	int C[line+1][row+1]; //storge the position of every row,a position for the flag_end

	for(int i=0;i<line;i++) //get the array data from the keybord
	{
		cout<<"Input data of the line "<<i+1<<" ("<<row<<" integers)"<<endl;
		for(int j=0;j<row;j++)
		{
			cin >> A[i][j];
		}
		while((ch=getchar()!='\n') && (ch!=EOF)); //fflush the stdin
	}

	cout << endl;

	cout << "Check your input:" << endl;
	for(int i=0;i<line;i++)
	{
		for(int j=0;j<row;j++)
		{
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}

	for(int i=0;i<line;i++) //get the min position of every line
	{
		min=A[i][0];
		B[i][0]=0;
		int m=0;
		for(int j=1;j<row;j++)
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

	for(int j=0;j<row;j++) //get the max position of every row
	{
		max=A[0][j];
		C[j][0]=0;
		int n=0;
		for(int i=1;i<line;i++)
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
	for(int i=0;i<line;i++)
	{
		for(int j=0;B[i][j]!=flag_end;j++)
		{
			cout << B[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl;

	cout << "The biggest position of every row:" <<endl;
	for(int j=0;j<row;j++)
	{
		for(int i=0;C[j][i]!=flag_end;i++)
		{
			cout << C[j][i] << "\t";
		}
		cout << endl;
	}

	for(int i=0;i<line;i++)
	{
		for(int m=0;B[i][m]!=flag_end;m++)
		{
			for(int n=0;C[B[i][m]][n]!=flag_end;n++)
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
