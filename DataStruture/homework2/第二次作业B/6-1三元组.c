#include<stdio.h>
#define ElemType int
#define M 4
#define N 4
typedef struct
{
	int r;
	int c;
	ElemType d;
}TupNode;
typedef struct
{
	int rows;
	int cols;
	int nums; //非零个数
	TupNode data[10];
}TSMatrix;
void CreateMat(TSMatrix *t, ElemType A[M][N])
{
	int i, j;
	(*t).rows = M;
	(*t).cols = N;
	(*t).nums = 0;
	for(i=0;i<M;i++)
		for (j = 0; j < N; j++)
		{
			if (A[i][j] != 0)
			{
				(*t).data[(*t).nums].r = i;
				(*t).data[(*t).nums].c = j;
				(*t).data[(*t).nums].d = A[i][j];
				(*t).nums++;

			}
		}
}
void DispMat(TSMatrix t)
{
	int k;
	if (t.nums <= 0)
		return;
	printf("%d %d %d\n", t.rows, t.cols, t.nums);
	printf("_ _ _\n\n");
	for(k=0;k<t.nums;k++)
		printf("%d %d %d\n", t.data[k].r, t.data[k].c, t.data[k].d);

}

void TranTat(TSMatrix a, TSMatrix *b)
{
	int ka, kb = 0, v;
	(*b).cols = a.rows;
	(*b).rows = a.cols;
	(*b).nums = a.nums;
	if (a.nums == 0)
		return;
	for(v=0;v<a.cols;v++)
		for (ka = 0; ka < a.nums; ka++)
		{
			if (a.data[ka].c == v)
			{
				(*b).data[kb].r = a.data[ka].c;
				(*b).data[kb].c = a.data[ka].r;
				(*b).data[kb].d = a.data[ka].d;
				kb++;
			}
		}
}

void create_a_and_b(int *a[], int *b[], int m, int n, int *c[])
{
	int i, j;
	for(i=0;i<m;i++)
		for (j = 0; j < n; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
}
int main(void)
{
	TSMatrix A, B, TA, C, D;
	//C:a+b  D:a*b:
	int a[4][4] = {
		{1,0,3,0},{0,1,0,0},{0,0,1,0},{0,0,1,1}
	};
	int b[4][4] = {
		{3,0,0,0},{0,4,0,0},{0,0,1,0},{0,0,0,2}
	};
	int c[4][4];
	int d[4][4];
	CreateMat(&A, a);
	TranTat(A,&TA);
	printf("a转置矩阵的三元组：\n");
	DispMat(TA); //输出转置矩阵

	//构建a+b
	int i, j;
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	CreateMat(&C, c);
	printf("a+b的三元组：\n");
	DispMat(C);

	int h;
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
			d[i][j] = 0;
		}
	for(i=0;i<M;i++)
		for (j = 0; j < N; j++)
		{
			for (h = 0; h < 4; h++)
				d[i][j] += a[i][h] * b[h][j];
		}

	CreateMat(&D, d);
	printf("a*b的三元组：\n");
	DispMat(D); //输出转置矩阵
	return 0;


}