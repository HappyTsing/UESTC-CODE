#include <stdio.h>
#include<stdbool.h>

#define M 4 //行数
#define N 4 //列数
#define MaxSize 100 //栈最多元素个数

// mg为迷宫二维数组:一个迷宫,其四周加上均为1的边框
int mg[M + 2][N + 2] = 
{
	{1, 1, 1, 1, 1, 1},{1, 0, 0, 0, 1, 1},{1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1},{1, 1, 0, 0, 0, 1},{1, 1, 1, 1, 1, 1}
};

// 定义栈和存放最短路径的数组
typedef struct
{
	int i; // 横坐标
	int j; // 纵坐标
	int di;
}Box;

Box St[MaxSize], Path[MaxSize];

int top = -1; //栈顶指针
int cnt = 1; //路径数计数
int minlen = MaxSize; //最短路径长度


 void disp_min_path(void);
 void disp_path(void); 
 void mgpath(int xi, int yi, int xe, int ye);
//功能:输出一条路径并求最短路径
int main(void)
{
	printf("迷宫所有路径:\n");
	mgpath(1, 1, M, N);

	return 0;
}
void disp_path(void)
{
	int k;

	printf("  %5d: ", cnt++); // 输出第cnt条路径
	for (k = 0; k <= top; k++)
		printf("(%d,%d)", St[k].i, St[k].j);
	printf("\n");

	if (top + 1 < minlen) //比较找最短路径
	{
		for (k = 0; k <= top; k++) //将最短路径存放在path中
			Path[k] = St[k];
		minlen = top + 1; // 将最短路径长度存放在minlen中
	}
}


//  功能:输出第一条最短路径

 void disp_min_path(void)
{
	int k;

	printf("\n最短路径:");

	for (k = 0; k < minlen; k++)
		printf("(%d,%d)", Path[k].i, Path[k].j);
	printf("\n最短路径长度: %d\n", minlen);
	printf("\n");
}

/**
*   xi:入口横坐标
*   yi:入口纵坐标
*   xe:出口横坐标
*   ye:出口纵坐标
*/
void mgpath(int xi, int yi, int xe, int ye)
{
	int i, j, i1, j1, di;
	bool find;

	top++; // 进栈
	St[top].i = xi;
	St[top].j = yi;
	St[top].di = -1; mg[xi][yi] = -1; // 初始方块进栈,置-1避免重复走，避免死循环
	while (top > -1) // 栈不空时循环
	{
		i = St[top].i; j = St[top].j; // 取栈顶方块(i,j)
		di = St[top].di;
		if (i == xe && j == ye) // 找到了出口
		{
			disp_path(); // 输出一条路径
			mg[i][j] = 0; // 让出口变为其他路径可走方块
			top--; // 出口退栈,即回退一个方块
			i = St[top].i; j = St[top].j;
			di = St[top].di; // 让栈顶方块变为当前方块
		}
		find = false; // 找下一个可走方块(i1,j1);
		while (di < 4 && !find)
		{
			di++;
			switch (di)
			{
			case 0:
				i1 = i - 1;
				j1 = j;
				break;
			case 1:
				i1 = i;
				j1 = j + 1;
				break;
			case 2:
				i1 = i + 1;
				j1 = j;
				break;
			case 3:
				i1 = i;
				j1 = j - 1;
				break;
			}
			if (mg[i1][j1] == 0)
				find = true;
		}
		if (find) // 找到了下一个可走方块(i1,j1)
		{
			St[top].di = di; // 修改原栈顶元素的di值
			top++; St[top].i = i1, St[top].j = j1;
			St[top].di = -1; // 下一个可走方块(i1,j1)进栈
			mg[i1][j1] = -1; // 避免重复走到该方块
		}
		else // 没有路径可走,则(i,j)方块退栈
		{
			mg[i][j] = 0; // 让该位置变为其他路径可走方块
			top--;
		}
	}
	disp_min_path(); // 输出最短路径
}


