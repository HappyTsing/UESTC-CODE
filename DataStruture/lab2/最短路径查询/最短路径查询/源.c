#include<stdio.h>	
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#define MAXV 6
#define INF 32767  //定义最大值
#define InfoType int

typedef struct linkpath
{
	int begin;
	int end;
	int path[MAXV];
	int length;
	int num;
	struct linkpath *next;
}Floydpath;
typedef struct
{
	Floydpath *next;
}Head_graph;

typedef struct
{
	int edges[MAXV][MAXV];
	int n; //n顶点数 
	char *name[MAXV] ;
}MatGraph;

void Dijkstra_Dispath(MatGraph g, int dist[], int path[], int s[], int v_begin,int v_end);
void Dijkstra(MatGraph g, int v_begin, int v_end);
void init_graph_save(MatGraph *g);
void read_create_Matgraph(MatGraph *g);
void Floyd(MatGraph g);
void Floyd_Dispath_printf(MatGraph g, int A[][MAXV], int path[][MAXV]);
void Floyd_save(MatGraph g, Head_graph *H_gra);
void Floyd_Dispath_save(MatGraph g, int A[][MAXV], int path[][MAXV], Head_graph *H_gra);
void read_create_Linkgraph(Head_graph *H_gra);
void search(MatGraph g, Head_graph H_gra);
void welcome(void);

int main(void)
{
	int choice;
	MatGraph G;
	Head_graph H_gra;
	H_gra.next = NULL;
	char name_begin[20], name_end[20];
	int j, v_begin, v_end;
	welcome();
	while (1)
	{
		printf("\n请输入测试功能：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:init_graph_save(&G); break;
		case 2:
			read_create_Matgraph(&G);
			printf("请输入起始点和终点的景点名:");
			scanf("%s", name_begin);
			scanf("%s", name_end);
			for (j = 0; j < G.n; j++)
			{
				if (strcmp(name_begin, G.name[j]) == 0)
				{
					v_begin = j;
				}
				if (strcmp(name_end, G.name[j]) == 0)
				{
					v_end = j;
				}
			}
			Dijkstra(G, v_begin, v_end);
			break;
		case 3:
			read_create_Matgraph(&G);
			Floyd_save(G, &H_gra);
			break;
		case 4:
			read_create_Matgraph(&G);
			Floyd(G);
			break;
		case 5:
			read_create_Matgraph(&G);
			read_create_Linkgraph(&H_gra);
			search(G, H_gra);
			break;

		case 6:
			return 0;
		}
	}

	return 0;

}
void init_graph_save(MatGraph *g)
{
	int flag = 0;
	int i,j, distance, m = 0, n = 0;
	char quit;
	FILE *fp;
	(*g).n = 6;
	(*g).name[0] = "JD0";
	(*g).name[1] = "JD1";
	(*g).name[2] = "JD2";
	(*g).name[3] = "JD3";
	(*g).name[4] = "JD4";
	(*g).name[5] = "JD5";

	char name1[20], name2[20];
	//初始设置为无限大距离\0;
	for (i = 0; i < (*g).n; i++)
	{
		for (j = 0; j < (*g).n; j++)
		{
			if (i != j)
				(*g).edges[i][j] = INF;
			else
				(*g).edges[i][j] = 0;

		}
	}
	while (1)
	{
		printf("输入两个景点名字和距离 格式：景点1名字 景点2名字 距离：");
		scanf("%s", name1);
		scanf("%s", name2);
		scanf("%d", &distance);
	
		for (j = 0; j < (*g).n; j++)
		{
			if (strcmp(name1, (*g).name[j]) == 0)
			{
				m = j;
				flag += 1;
			}
			if (strcmp(name2, (*g).name[j]) == 0)
			{
				n = j;
				flag += 1;
			}
		}
		if (flag==2)
		{
			(*g).edges[m][n] = distance; (*g).edges[n][m] = distance;
		}
		else
			printf("错误输入");

		flag = 0;

		printf("继续输入？按Q退出,按任意键继续");
		scanf(" %c", &quit);
		if (quit == 'q' || quit == 'Q')
			break;
		while ((quit = getchar()) != EOF && quit != '\n');  //清空输入缓存
	}
	fp=fopen("graph.dat", "w");
	for (i = 0; i < (*g).n; i++)
	{
		for (j = 0; j < (*g).n; j++)
		{
			fprintf(fp, "%d ", (*g).edges[i][j]);
		}
		fprintf(fp, "\n");
	}


	fclose(fp);
}
void read_create_Matgraph(MatGraph *g)
{
	int i, j;
	FILE *fp;
	fp = fopen("graph.dat", "r");
	(*g).n = MAXV;
	(*g).name[0] = "JD0";
	(*g).name[1] = "JD1";
	(*g).name[2] = "JD2";
	(*g).name[3] = "JD3";
	(*g).name[4] = "JD4";
	(*g).name[5] = "JD5";
	for (i = 0; i < (*g).n; i++)
	{
		for (j = 0; j < (*g).n; j++)
		{
			fscanf(fp, "%d", &(*g).edges[i][j]);
		}
	}

}
void Dijkstra_Dispath(MatGraph g, int dist[], int path[], int s[], int v_begin,int v_end)

{
	int  j, k;
	int apath[MAXV], d;
		if (s[v_end] == 1 && v_end != v_begin)
		{
			printf("从顶点%d到顶点%d的路径长度为：%d\t路径为：", v_begin, v_end, dist[v_end]);
			d = 0;
			apath[d] = v_end;   //路径终点是v_end
			k = path[v_end];
			if (k == -1)
				printf("无路径\n");
			else
				while (k != v_begin)
				{
					d++;
					apath[d] = k;    //path[k]是k-1个路径顶点值
					k = path[k];
				}
			d++;
			apath[d] = v_begin;  //路径起点是v_begin
			for (j = d ; j >0; j--)   //apath是倒叙存储路径
				printf("%s-", g.name[apath[j]]);
		
			printf("%s", g.name[apath[j]]);
			printf("\n");
		}
}
void Dijkstra(MatGraph g, int v_begin,int v_end)
{
	int dist[MAXV], path[MAXV];    //path[i]中储存的是顶点i的前一个顶点  dist用于储存源点v到其他各个顶点的路径最短值
	int s[MAXV];  //储存超点 s[]=1 表示在s中  s[]=0 表示顶点不在s中 
	int MINdis, i, j, u;
	for (i = 0; i < g.n; i++)   //此循环用于初始化
	{
		dist[i] = g.edges[v_begin][i];
		s[i] = 0; // 置0
		if (g.edges[v_begin][i] < INF)
			path[i] = v_begin;
		else
			path[i] = -1;     //顶点v到顶点i无边
	}
	s[v_begin] = 1; path[v_begin] = 0;   //源点v放入s中
	for (i = 0; i < g.n - 1; i++)
	{
		MINdis = INF;
		for (j = 0; j < g.n; j++)  //选取不在s中且具有最小最短路径长度的顶点u；
			if (s[j] == 0 && dist[j] < MINdis)
			{
				u = j;
				MINdis = dist[j];
			}
		s[u] = 1;  //将顶点u加入s
		for (j = 0; j < g.n; j++)   //修改与u相邻的点的权值为最小
			if (s[j] == 0)
				if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j])
				{
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dijkstra_Dispath(g, dist, path, s, v_begin,v_end);
}
void Floyd(MatGraph g)
{
	int A[MAXV][MAXV], path[MAXV][MAXV];
	int i, j, k;
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;
			else
				path[i][j] = -1;
		}
	for (k = 0; k < g.n; k++)
	{
		for(i=0;i<g.n;i++)
			for (j = 0; j < g.n; j++)
			{
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[k][j];
				}
			}
	}
	Floyd_Dispath_printf(g, A, path);
}
void Floyd_Dispath_printf(MatGraph g, int A[][MAXV], int path[][MAXV])
{
	int i, j, k, s;
	int apath[MAXV], d;
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++)
		{
			if (A[i][j] != INF && i != j)
			{

				printf("从%s到%s的路径长度为：%d\t", g.name[i], g.name[j], A[i][j]);
				printf("路径为：");

				k = path[i][j];
				d = 0;
				apath[d] = j;//添加终点/倒序
				while (k != -1 && k != i)
				{
					d++;
					apath[d] = k;
					k = path[i][k];

				}
				d++; apath[d] = i;
				printf("%s", g.name[apath[d]]);
				for (s = d-1; s >= 0; s--)
				{
					printf("-%s", g.name[apath[s]]);
				}
				printf("\n");
		
			}
		}
}

void Floyd_save(MatGraph g, Head_graph *H_gra)
{
	int A[MAXV][MAXV], path[MAXV][MAXV];
	int i, j, k;
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;
			else
				path[i][j] = -1;
		}
	for (k = 0; k < g.n; k++)
	{
		for (i = 0; i < g.n; i++)
			for (j = 0; j < g.n; j++)
			{
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[k][j];
				}
			}
	}
	Floyd_Dispath_save(g, A, path,H_gra);
}
void Floyd_Dispath_save(MatGraph g, int A[][MAXV], int path[][MAXV],Head_graph *H_gra)
{
	int i, j, k, s,w=0;
	Floydpath *p;
	int apath[MAXV], d;
	FILE *fp;
	(*H_gra).next = NULL;

	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
		{
			if (A[i][j] != INF && i != j)
			{

				k = path[i][j];
				d = 0;
				apath[d] = j;//添加终点/倒序
				while (k != -1 && k != i)
				{
					d++;
					apath[d] = k;
					k = path[i][k];

				}
				d++; apath[d] = i;

				p = (Floydpath*)malloc(sizeof(Floydpath));
				p->begin = i;
				p->end = j;
				p->length = A[i][j];
				w = 0;
				p->next = NULL;
				p->num = d + 1;
				for (s = d ; s >= 0; s--)
				{
					p->path[w] = apath[s];
					w++;
				}
				if ((*H_gra).next == NULL)
					(*H_gra).next = p;
				else
				{
					p->next = (*H_gra).next;
					(*H_gra).next = p;
				}

			}
		}
	fp = fopen("AllPath.dat", "w");
	if (fp == NULL)
	{
		perror("文件打开失败：");
		exit(EXIT_FAILURE);
	}
	p = (*H_gra).next;
	while (p != NULL)
	{
		if (fwrite(p, sizeof(Floydpath), 1, fp)==1)
			p = p->next;
	}
	fclose(fp);
}
void read_create_Linkgraph(Head_graph *H_gra)
{
	FILE *fp;
	Floydpath *p;
	fp= fopen("AllPath.dat", "r");
	if (fp == NULL)
	{
		perror("文件打开失败：");
		exit(EXIT_FAILURE);
	}
	for (;;)
	{
		p = (Floydpath*)malloc(sizeof(Floydpath));
		if (p == NULL)
		{
			perror("读入信息分配空间失败：");
			exit(EXIT_FAILURE);
		}
		if (fread(p, sizeof(Floydpath), 1, fp) == 1)
		{
			p->next = (*H_gra).next;
			(*H_gra).next = p;

		}
		else
			break;
	}
	fclose(fp);


}
void search(MatGraph g,Head_graph H_gra)
{
	int i;
	char name_begin[20], name_end[20];
	printf("\n请输入所查询路径的起始点和终点的景点名:");
	scanf("%s", name_begin);
	scanf("%s", name_end);
	Floydpath *p;
	p = H_gra.next;
	while (p != NULL)
	{
		if (strcmp(name_begin, g.name[p->begin]) == 0 && strcmp(name_end, g.name[p->end]) == 0)
		{
			printf("\n路径长度为：%d\t", p->length);
			printf("路径为：");
			printf("%s", g.name[p->begin]);
			for (i = 1; i < p->num; i++)
			{
				printf("-%s", g.name[p->path[i]]);
			}

		}
		p = p->next;

	}

}

void welcome(void)
{
	printf("*********公园景点间的最短路径查询系统*********\n");
	printf("****1.输入景点名字和距离并将其存盘        ****\n");
	printf("****2.dijkstra算法计算景点间的最短路径    ****\n");
	printf("****3.Floyd算法计算所有景点最短路径并存盘 ****\n");
	printf("****4.Floyd算法打印所有景点对间最短路径   ****\n");
	printf("****5.读盘构建链表实现最短路径查询        ****\n");
	printf("****6.退出系统                            ****\n");
	printf("**********************************************\n");
}