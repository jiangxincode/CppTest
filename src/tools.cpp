#include <fstream>
#include <string>
#include <iostream>

#include "main.h"

using namespace std;

bool compare_file_binary(string filename1, string filename2)
{
    fstream file1,file2;
	char ch1,ch2;

	file1.open(filename1.c_str(),ios::binary|ios::in);
	file2.open(filename2.c_str(),ios::binary|ios::in);

	if(!(file1.is_open() && file2.is_open()))
	{
		return false;
	}

	while(file1.get(ch1) && file2.get(ch2))
	{
		if(ch1 != ch2)
		{
			file1.close();
			file2.close();
			return false;
		}
	}
	if(!file1.get(ch1) && !file2.get(ch2))
	{
		file1.close();
		file2.close();
		return true;
	}

	file1.close();
	file2.close();
	return false;
}

bool compare_file_text(string filename1, string filename2)
{
    fstream file1,file2;
	string str1,str2;

	file1.open(filename1.c_str(),ios::in);
	file2.open(filename2.c_str(),ios::in);

	if( !(file1.is_open() && file2.is_open() ) )
	{
		return false;
	}

	while(getline(file1, str1) && getline(file2, str2))
	{
		if(str1.compare(str2) != 0)
		{
			cerr << "The expect is: " << str1 << endl;
			cerr << "The actuall is: " << str2 << endl;
			file1.close();
			file2.close();
			return false;
		}
	}
	if(!getline(file1, str1) && !getline(file2, str2))
	{
		file1.close();
		file2.close();
		return true;
	}

	file1.close();
	file2.close();
	return false;
}
