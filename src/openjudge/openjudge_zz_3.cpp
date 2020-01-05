/**
 * 文字排版
 * http://ica.openjudge.cn/zz/3
 * 描述给一段英文短文，单词之间以空格分隔（每个单词包括其前后紧邻的标点符号）。
 * 请将短文重新排版，要求如下：
 * 每行不超过80个字符；每个单词居于同一行上；在同一行的单词之间以一个空格分隔；行首和行尾都没有空格。
 * 输入
 * 第一行是一个整数n，表示英文短文中单词的数目. 其后是n个以空格分隔的英文单词（单词包括其前后紧邻的标点符号，且每个单词长度都不大于40个字母）。
 * 输出
 * 排版后的多行文本，每行文本字符数最多80个字符，单词之间以一个空格分隔，每行文本首尾都没有空格。
 * 样例输入
 * 84
 * One sweltering day, I was scooping ice cream into cones and told my four children they could "buy" a cone from me for a hug. Almost immediately, the kids lined up to make their purchases. The three youngest each gave me a quick hug, grabbed their cones and raced back outside. But when my teenage son at the end of the line finally got his turn to "buy" his ice cream, he gave me two hugs. "Keep the changes," he said with a smile.
 * 样例输出
 * One sweltering day, I was scooping ice cream into cones and told my four
 * children they could "buy" a cone from me for a hug. Almost immediately, the kids
 * lined up to make their purchases. The three youngest each gave me a quick hug,
 * grabbed their cones and raced back outside. But when my teenage son at the end
 * of the line finally got his turn to "buy" his ice cream, he gave me two hugs.
 * "Keep the changes," he said with a smile.
 *
 */
#include <iostream>
#include <cstring>

using namespace std;

#define MAX_WORD_NUMBER 1000
#define MAX_WORD_LENGHT 40
#define MAX_CHAR_PER_LINE 80

int main()
{
	char words[MAX_WORD_NUMBER][MAX_WORD_LENGHT]; //用于保存每一个单词
	int wordsLen[MAX_WORD_NUMBER]; // 记录每一个单词的长度
	int n; // 需要处理的单词总数

	cin >> n;
	for (int i = 0; i < n; i++) //输入单词数据，处理后得到每个单词的长度
	{
		cin >> words[i];
		wordsLen[i] = strlen(words[i]);

	}

	//其实可以将读入过程和输出过程合并到一起，可以节省空间，提高效率，但是会导致输入和输出在一起比较混乱，所以分开处理
	int length = 0;
	for (int i = 0; i < n; i++)
	{
		if (length == 0) //当前行没有任何内容
		{
			length = wordsLen[i];
			cout << words[i];
		}
		else if (length + 1 + wordsLen[i] <= MAX_CHAR_PER_LINE) //如果该单词，连同前面的一个空格加入后不换行，则输出空格和该单词
		{
			length = length + 1 + wordsLen[i];
			cout << " " << words[i];
		}
		else
		{
			cout << endl;
			length = wordsLen[i];
			cout << words[i];
		}
	}
	cout << endl;
	return 0;
}
