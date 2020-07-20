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
	BTNode data[10];
	int top;

} SqStack;

typedef struct
{
	BTNode *data[10];
	int front, rear;

} SqQueue;


void DestroyStack(SqStack **e);
bool GetTop(SqStack*s, BTNode** e);
bool Pop(SqStack**s, BTNode **e);
bool Push(SqStack**s, BTNode *e);
bool StackEmpty(SqStack *s);
void InitStack(SqStack **s);

void DestroyQueue(SqQueue **q);
bool enQueue(SqQueue**q, BTNode *c);
bool deQueue(SqQueue**q, BTNode** c);
bool QueueEmpty(SqQueue *q);
void InitQueue(SqQueue **q);

void d_PreOrder(BTNode *b);
void d_InOrder(BTNode *b);
void d_PostOrder(BTNode *b);

void PreOrder(BTNode *b);
void InOrder(BTNode *b);
void PostOrder(BTNode *b);

void LevelQueue(BTNode *b);

void CreatBTree(BTNode **b, const char *str);
int main(void)
{
	BTNode *t;
	CreatBTree(&t, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("递归   前序：");
	d_PreOrder(t);
	printf("\n非递归 前序：");
	PreOrder(t);
	printf("\n\n递归   中序：");
	d_InOrder(t);
	printf("\n非递归 中序：");
	InOrder(t);
	printf("\n\n递归   后序：");
	d_PostOrder(t);
	printf("\n非递归 后序：");
	//PostOrder(t);
	d_PostOrder(t);
	printf("\n\n层次   排序：");
	LevelQueue(t);

	return 0;
}

void d_PreOrder(BTNode *b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		d_PreOrder(b->lchild);
		d_PreOrder(b->rchild);
	}
}
void d_InOrder(BTNode *b)
{
	if (b != NULL)
	{
		d_InOrder(b->lchild);
		printf("%c", b->data);
		d_InOrder(b->rchild);
	}
}
void d_PostOrder(BTNode *b)
{
	if (b!=NULL)
	{
		d_PostOrder(b->lchild);
		d_PostOrder(b->rchild);
		printf("%c", b->data);
	}
}

void PreOrder(BTNode *b)
{
	BTNode *p;
	SqStack *st;
	InitStack(&st);
	p = b;
	while (!StackEmpty(st) || p != NULL)
	{
		while (p != NULL)
		{
			printf("%c", p->data);
			Push(&st, p);
			p = p->lchild;
		}
		if (!StackEmpty(st))
		{
			Pop(&st, &p);
			p = p->rchild;
		}
	}
	printf("\n");
	DestroyStack(&st);
}
void InOrder(BTNode *b)
{
	BTNode *p;
	SqStack *st;
	InitStack(&st);
	p = b;
	while (!StackEmpty(st) || p != NULL)
	{
		while (p != NULL)
		{

			Push(&st, p);
			p = p->lchild;
		}
		if (!StackEmpty(st))
		{
			Pop(&st, &p);
			printf("%c", p->data);
			p = p->rchild;
		}
	}
	printf("\n");
	DestroyStack(&st);
}
void PostOrder(BTNode *b)
{
	BTNode *p, *r;
	bool flag;
	SqStack *st;
	InitStack(&st);
	p = b;
	do
	{
		while (p != NULL)
		{

			Push(&st, p);
			p = p->lchild;
		}
		r = NULL;  //r指向刚刚访问过的节点，初始为空 
		flag = true;//为真表示正在处理栈顶节点 
		while (!StackEmpty(st) && flag)
		{
			GetTop(st, &p);
			if (p->rchild == r)
			{
				printf("%c", p->data);
				Pop(&st, &p);
				r = p;
			}
			else
			{
				p = p->rchild;
				flag = false;
			}
		}

	} while (!StackEmpty(st));
	printf("\n");
	DestroyStack(&st);
}

void LevelQueue(BTNode *b)
{
	BTNode *p;
	SqQueue *qu;
	InitQueue(&qu);
	enQueue(&qu, b);
	while (!QueueEmpty(qu))
	{
		deQueue(&qu, &p);
		printf("%c", p->data);
		if (p->lchild != NULL)
			enQueue(&qu, p->lchild);
		if (p->rchild != NULL)
			enQueue(&qu, p->rchild);

	}
}

void InitStack(SqStack **s)
{
	*s = (SqStack*)malloc(sizeof(SqStack));
	(*s)->top = -1;
}
bool StackEmpty(SqStack *s)
{
	return s->top == -1;
}
bool Push(SqStack**s, BTNode *e)
{
	if ((*s)->top == 9)
		return false;
	(*s)->top++;
	(*s)->data[(*s)->top] = *e;
	return true;

}
bool Pop(SqStack**s, BTNode** e)
{
	if (StackEmpty(*s))
		return false;
	*e = (BTNode*)malloc(sizeof(BTNode));
	**e= (*s)->data[(*s)->top];
	(*s)->top--;
	return true;
}
bool GetTop(SqStack*s, BTNode** e)
{
	if (StackEmpty(s))
		return false;
	*e = (BTNode*)malloc(sizeof(BTNode));
	**e = (s)->data[(s)->top];
	return true;
}
void DestroyStack(SqStack **q)
{
	free(*q);
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


void CreatBTree(BTNode **b,const char *str)
{
	BTNode *st[10], *p=NULL;
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
