#include<stdio.h>	
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#define MAXV 6
#define INF 32767  //�������ֵ
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
	int n; //n������ 
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
		printf("\n��������Թ��ܣ�");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:init_graph_save(&G); break;
		case 2:
			read_create_Matgraph(&G);
			printf("��������ʼ����յ�ľ�����:");
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
	//��ʼ����Ϊ���޴����\0;
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
		printf("���������������ֺ;��� ��ʽ������1���� ����2���� ���룺");
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
			printf("��������");

		flag = 0;

		printf("�������룿��Q�˳�,�����������");
		scanf(" %c", &quit);
		if (quit == 'q' || quit == 'Q')
			break;
		while ((quit = getchar()) != EOF && quit != '\n');  //������뻺��
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
			printf("�Ӷ���%d������%d��·������Ϊ��%d\t·��Ϊ��", v_begin, v_end, dist[v_end]);
			d = 0;
			apath[d] = v_end;   //·���յ���v_end
			k = path[v_end];
			if (k == -1)
				printf("��·��\n");
			else
				while (k != v_begin)
				{
					d++;
					apath[d] = k;    //path[k]��k-1��·������ֵ
					k = path[k];
				}
			d++;
			apath[d] = v_begin;  //·�������v_begin
			for (j = d ; j >0; j--)   //apath�ǵ���洢·��
				printf("%s-", g.name[apath[j]]);
		
			printf("%s", g.name[apath[j]]);
			printf("\n");
		}
}
void Dijkstra(MatGraph g, int v_begin,int v_end)
{
	int dist[MAXV], path[MAXV];    //path[i]�д�����Ƕ���i��ǰһ������  dist���ڴ���Դ��v���������������·�����ֵ
	int s[MAXV];  //���泬�� s[]=1 ��ʾ��s��  s[]=0 ��ʾ���㲻��s�� 
	int MINdis, i, j, u;
	for (i = 0; i < g.n; i++)   //��ѭ�����ڳ�ʼ��
	{
		dist[i] = g.edges[v_begin][i];
		s[i] = 0; // ��0
		if (g.edges[v_begin][i] < INF)
			path[i] = v_begin;
		else
			path[i] = -1;     //����v������i�ޱ�
	}
	s[v_begin] = 1; path[v_begin] = 0;   //Դ��v����s��
	for (i = 0; i < g.n - 1; i++)
	{
		MINdis = INF;
		for (j = 0; j < g.n; j++)  //ѡȡ����s���Ҿ�����С���·�����ȵĶ���u��
			if (s[j] == 0 && dist[j] < MINdis)
			{
				u = j;
				MINdis = dist[j];
			}
		s[u] = 1;  //������u����s
		for (j = 0; j < g.n; j++)   //�޸���u���ڵĵ��ȨֵΪ��С
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

				printf("��%s��%s��·������Ϊ��%d\t", g.name[i], g.name[j], A[i][j]);
				printf("·��Ϊ��");

				k = path[i][j];
				d = 0;
				apath[d] = j;//����յ�/����
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
				apath[d] = j;//����յ�/����
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
		perror("�ļ���ʧ�ܣ�");
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
		perror("�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}
	for (;;)
	{
		p = (Floydpath*)malloc(sizeof(Floydpath));
		if (p == NULL)
		{
			perror("������Ϣ����ռ�ʧ�ܣ�");
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
	printf("\n����������ѯ·������ʼ����յ�ľ�����:");
	scanf("%s", name_begin);
	scanf("%s", name_end);
	Floydpath *p;
	p = H_gra.next;
	while (p != NULL)
	{
		if (strcmp(name_begin, g.name[p->begin]) == 0 && strcmp(name_end, g.name[p->end]) == 0)
		{
			printf("\n·������Ϊ��%d\t", p->length);
			printf("·��Ϊ��");
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
	printf("*********��԰���������·����ѯϵͳ*********\n");
	printf("****1.���뾰�����ֺ;��벢�������        ****\n");
	printf("****2.dijkstra�㷨���㾰�������·��    ****\n");
	printf("****3.Floyd�㷨�������о������·�������� ****\n");
	printf("****4.Floyd�㷨��ӡ���о���Լ����·��   ****\n");
	printf("****5.���̹�������ʵ�����·����ѯ        ****\n");
	printf("****6.�˳�ϵͳ                            ****\n");
	printf("**********************************************\n");
}