//迷宫
#include <stack>
#include <iostream>
#include <cstdio>

using namespace std;

// start : Postion(2, 1), end : Postion(6, 8)
int maze[10][10] = {{ 0, 0, 0, 0,-1, 0, 0, 0, 0, 0},
    { 0,-1,-1, 0, 0, 0, 0,-1, 0, 0},
    { 0, 0,-1, 0,-1, 0, 0,-1, 0,-1},
    { 0, 0,-1, 0,-1, 0, 0,-1, 0,-1},
    { 0, 0, 0, 0,-1,-1, 0,-1, 0, 0},
    { 0, 0,-1, 0, 0, 0, 0, 0, 0, 0},
    { 0,-1, 0, 0,-1, 0,-1,-1, 0, 0},
    { 0, 0, 0,-1, 0, 0, 0,-1, 0,-1},
    {-1, 0, 0,-1, 0, 0, 0,-1, 0,-1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0,-1}
};



struct Postion
{
    int _X, _Y;

    Postion() {}
    Postion(int X, int Y)
        : _X(X), _Y(Y) {}
};

static void printPath(stack<Postion> path)
{
    while(!path.empty())
    {
        printf("[%d][%d] ==>> [%2d]\n",
               path.top()._X, path.top()._Y,
               maze[path.top()._X][path.top()._Y]-1);
        path.pop();
    }
}

static void	printMat(int mat[10][10])
{
    for(int i = 0; i < 10 ; i++)
    {
        for(int j = 0; j < 10 ; j++)
        {
            printf("%2d ", mat[i][j]);
        }

        printf("\n");
    }
}

static bool isCanGo(const int prePosValue,
             const int posX,
             const int posY)
{
    if(posX < 0 || posX > 9		// 越界
            || posY < 0 || posY > 9
            || maze[posX][posY] == -1)	// 墙
    {
        return false;
    }

    if(maze[posX][posY] == 0)	// 未走过
    {
        return true;
    }
    else						// 更近的路径
    {
        return (prePosValue + 1) < maze[posX][posY];
    }
}


static stack<Postion> path__;			// 路径

static Postion offset[4];				// 偏移量

static void shortestPath(stack<Postion> &path,
                  const Postion &start,
                  const Postion &end)
{
    if(start._X == end._X
            && start._Y == end._Y)
    {
        if(path.size() < path__.size() || path__.empty())	// 更短的路径
        {
            path__ = path;
        }

        return;
    }

    for(int i = 0; i < 4; i++)
    {
        int nNextPos_X = start._X + offset[i]._X;
        int nNextPos_Y = start._Y + offset[i]._Y;

        if(isCanGo(maze[start._X][start._Y], nNextPos_X, nNextPos_Y))
        {
            maze[nNextPos_X][nNextPos_Y] = maze[start._X][start._Y] + 1;
            path.push(Postion(nNextPos_X, nNextPos_Y));
            shortestPath(path, Postion(nNextPos_X, nNextPos_Y), end);
            path.pop();
        }
    }
}

int main0510()
{
    offset[0]._X = -1;
    offset[0]._Y = 0;	// 上
    offset[1]._X = 1;
    offset[1]._Y = 0;	// 下
    offset[2]._X = 0;
    offset[2]._Y = -1;	// 左
    offset[3]._X = 0;
    offset[3]._Y = 1;	// 右
    Postion start(2, 1), end(6, 8);
    maze[start._X][start._Y] = 1;			// 置起点值1, 防止走回起点
    stack<Postion> temp;
    shortestPath(temp, start, end);
    printPath(path__);
    printMat(maze);
    return 0;
}

