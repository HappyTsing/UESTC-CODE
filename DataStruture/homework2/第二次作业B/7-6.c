#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	struct node *lchild;
	struct node *rchild;

} BTNode;
typedef struct
{
	BTNode *data[10];
	int front, rear;

} SqQueue;


void DestroyQueue(SqQueue **q);
bool enQueue(SqQueue**q, BTNode *c);
bool deQueue(SqQueue**q, BTNode** c);
bool QueueEmpty(SqQueue *q);
void InitQueue(SqQueue **q);

void LevelQueue_len(BTNode *b, int *len_max);

void CreatBTree(BTNode **b, const char *str);
void caculate_num(BTNode *b, int* num);
void caculate_leafnum(BTNode *b, int *leafnum);
void caculate_printf_level(BTNode *b, char data, int level);
int main(void)
{
	BTNode *t;
	int num=0;
	int leafnum = 0;
	int level = 1; char data;
	int len_max;
	CreatBTree(&t, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	caculate_num(t, &num);
	printf("节点数：      %d", num);

	caculate_leafnum(t, &leafnum);
	printf("\n叶子节点数量: %d", leafnum);


	LevelQueue_len(t, &len_max);
	printf("\n宽度          %d", len_max);

	printf("\n输入你要查询的节点值");
	scanf(" %c", &data);
	caculate_printf_level(t,data,level);


	return 0;
}
void CreatBTree(BTNode **b, const char *str)
{
	BTNode *st[10], *p = NULL;
	int top = -1, k, j = 0;
	char ch;
	*b = NULL;
	ch = str[j];
	while (ch != '\0')
	{
		switch (ch)
		{
		case '(':top++; st[top] = p; k = 1; break;
		case')':top--; break;
		case',':k = 2; break;
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (*b == NULL)
				*b = p;
			else
			{
				switch (k)
				{
				case 1:st[top]->lchild = p; break;
				case 2:st[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}
void caculate_num(BTNode *b,int* num)
{
	if (b != NULL)
	{
		(*num)++;
		caculate_num(b->lchild,num);
		caculate_num(b->rchild,num);
	}
}
void caculate_leafnum(BTNode *b, int *leafnum)
{
	if (b == NULL)
		return;
	if (b->lchild == NULL && b->rchild == NULL)
		(*leafnum)++;
	caculate_leafnum(b->lchild, leafnum);
	caculate_leafnum(b->rchild, leafnum);

}
void caculate_printf_level(BTNode *b, char data,int level)
{
	if (b == NULL)
		return;
	if (data == b->data)
		printf("\n层次：        %d", level);

	level++;
	caculate_printf_level(b->lchild, data,level);
	caculate_printf_level(b->rchild, data,level);
	level--;


}
void LevelQueue_len(BTNode *b,int *len_max)
{ 
	// *len==1;
	BTNode *p;
	SqQueue *qu;
	InitQueue(&qu);
	enQueue(&qu, b);
	int len_last = 1;
	int len_now = 0;
	int record_last;
      (*len_max) = 1;
	while(!QueueEmpty(qu))
	{
		record_last = len_last;
		while (len_last!=0&& !QueueEmpty(qu))
		{
			deQueue(&qu, &p);
			len_last--;
			if (p->lchild != NULL)
			{
				enQueue(&qu, p->lchild);
				len_now++;
			}
			if (p->rchild != NULL)
			{
				enQueue(&qu, p->rchild);
				len_now++;
			}

		}
		(*len_max) = len_now > (*len_max) ? len_now : (*len_max);
		len_last =len_now;
		len_now = 0;


	}

}

void DestroyQueue(SqQueue **q)
{
	free(*q);
}
bool deQueue(SqQueue**q, BTNode** c)
{
	if (QueueEmpty(*q))
		return false;
	(*q)->front = ((*q)->front + 1) % 10;
	*c = (*q)->data[(*q)->front];
	return true;
}
bool enQueue(SqQueue**q, BTNode *c)
{
	if (((*q)->rear + 1) % 10 == (*q)->front)
		return false;
	(*q)->rear = ((*q)->rear + 1) % 10;
	(*q)->data[(*q)->rear] = c;
	return true;
}
bool QueueEmpty(SqQueue *q)
{
	return q->front == q->rear;
}
void InitQueue(SqQueue **q)
{
	*q = (SqQueue*)malloc(sizeof(SqQueue));
	(*q)->front = (*q)->rear = 0;
}
