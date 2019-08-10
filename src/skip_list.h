# include <iostream>

#include <cstdlib> //just for NULL
#include <climits> //just for INT_MAX and INT_MIN

const int DefaultSize = 100;

struct SkipNode
{
	int data;
	SkipNode **link;
	SkipNode(int size = DefaultSize)
	{
		link = new SkipNode *[size];
		if (link == NULL)
		{
			std::cerr << "存储分配失败！" << std::endl;
			exit(1);
		}
	}
	~SkipNode()
	{
		delete[] link;
	}
};

class SkipList
{
public:
	SkipList(int large, int maxLev = DefaultSize);
	~SkipList();
	bool Search(const )
};
