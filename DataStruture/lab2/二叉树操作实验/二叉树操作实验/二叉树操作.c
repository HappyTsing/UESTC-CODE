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

//��������
char str_tree[20];
int top1 = 0;
int top2 = 0;
int flag = 0;
void advance_printf(BTNode *b);
void CreatBTree_B1(BTNode **b, const char *str);
void create_str(BTNode *b);
void save_str(void);
void d_CreatBTree_new_B2(BTNode *b);
void d_create_tree_B2(BTNode *b, char tree[]);
void CreatBTree_new_B3(BTNode *my_tree);
void create_tree_B3(BTNode *my_tree, char tree[]);

//ջ����
bool GetTop(SqStack*s, BTNode** e);
void DestroyStack(SqStack **e);
bool Pop(SqStack**s, BTNode **e);
bool Push(SqStack**s, BTNode *e);
bool StackEmpty(SqStack *s);
void InitStack(SqStack **s);
//������
void InOrder(BTNode *b);
void PostOrder(BTNode *b);
//���ٺ���
void destroy_tree(BTNode ** T);
int main(void)
{
	BTNode *B1, *B2, *B3;
	B2 = (BTNode*)malloc(sizeof(BTNode));
	B3 = (BTNode*)malloc(sizeof(BTNode));
	CreatBTree_B1(&B1, "A(B(,C),D(,E(F,)))");
	create_str(B1);
	save_str();
	int top_remind = top1;
	d_CreatBTree_new_B2(B2);
	CreatBTree_new_B3(B3);

	top1 = 0;
	top2 = 0;
	printf("B1:");
	advance_printf(B1);
	printf("\n");
	printf("B2:");
	advance_printf(B2);
	printf("\n");
	printf("B3:");
	advance_printf(B3);
	printf("\n");
	printf("���������");
	InOrder(B1);
	printf("���������");
	PostOrder(B1);
	destroy_tree(&B1);
	destroy_tree(&B2);
	destroy_tree(&B3);

	return 0;

}

void advance_printf(BTNode *b)
{
	if (b == NULL)
	{
		printf("#");
		return;
	}
	else
	{
		printf("%c", b->data);
		advance_printf(b->lchild);
		advance_printf(b->rchild);

	}



}
void create_str(BTNode *b)
{

	BTNode *p = NULL;
	if (b == NULL)
	{

		str_tree[top1] = '#';
		top1++;
		return;
	}
	else
	{
		str_tree[top1] = b->data;
		top1++;
		create_str(b->lchild);
		create_str(b->rchild);
	}
}
void save_str(void)
{

	FILE *fp;
	fp = fopen("content.txt", "w");
	//str_tree[top1] = "\0";
	//top1++;  //topָ�������
	fprintf(fp, "%s", str_tree);
	fclose(fp);



}

void CreatBTree_B1(BTNode **b, const char *str)
{
	BTNode *st[20], *p = NULL;
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
void d_CreatBTree_new_B2(BTNode *b)
{
	top2 = 0;
	char tree[20];
	FILE *fp;
	fp = fopen("content.txt", "r");
	fscanf(fp, "%s", tree);
	fclose(fp);

	b->data = tree[top2];
	top2++;
	d_create_tree_B2(b, tree);
}
void d_create_tree_B2(BTNode *b, char tree[])
{

	if (top2 >= top1) return;
	if (tree[top2] == '#')
	{
		b->lchild = NULL;
		top2 += 1;
	}
	else
	{
		b->lchild = (BTNode*)malloc(sizeof(BTNode));
		b->lchild->data = tree[top2];
		top2++;
		d_create_tree_B2(b->lchild, tree);
	}
	if (tree[top2] == '#')
	{
		b->rchild = NULL;
		top2 += 1;
	}
	else
	{
		b->rchild = (BTNode*)malloc(sizeof(BTNode));
		b->rchild->data = tree[top2];
		top2++;
		d_create_tree_B2(b->rchild, tree);
	}
}
void CreatBTree_new_B3(BTNode *my_tree)
{
	top2 = 0;
	char tree[20];
	FILE *fp;
	fp = fopen("content.txt", "r");
	fscanf(fp, "%s", tree);
	fclose(fp);
	//��ʼ����һ��
	my_tree->data = tree[top2];
	top2++;
	d_create_tree_B2(my_tree, tree);

	create_tree_B3(my_tree, tree);
}
void create_tree_B3(BTNode *my_tree, char tree[])
{
	top2 = 1;
	BTNode *p, *b;
	SqStack *st;
	InitStack(&st);
	bool dir = true;
	while (top2 < top1)
	{
		while (tree[top2] != '#')
		{
			b = (BTNode*)malloc(sizeof(BTNode));
			b->data = tree[top2];
			if (StackEmpty(st))  //�գ���ջ
			{
				Push(&st, b);
				my_tree = b;
			}
			else        //���գ��жϷ����Ƿ���left������ջ��Ԫ�ص����ӵ��ڵ�һ�������Ľڵ㣬�����ڵ���ջ
			{
				if (dir)
				{
					GetTop(st, &p);
					p->lchild = b;

				}
				else    //����left���Һ��ӵ��ڽڵ㣬ɾ��ջ�����޸ķ���Ϊleft ��ջ�ڵ�
				{
					GetTop(st, &p);
					p->rchild = b;
					Pop(&st, &p);
					dir = true;
				}
				Push(&st, b);  //�ڵ���ջ��������һ��
			}
			top2++;
		}
		top2++;
		if (tree[top2] == '#')
		{
			if (!dir)    //�����ң���ջ�������󣬸�Ϊ������
			{
				Pop(&st, &p);
			}
			else
				dir = false;
		}

	}

	DestroyStack(&st);
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
	**e = (*s)->data[(*s)->top];
	(*s)->top--;
	return true;
}
void DestroyStack(SqStack **q)
{
	free(*q);
}
bool GetTop(SqStack*s, BTNode** e)
{
	if (StackEmpty(s))
		return false;
	*e = (BTNode*)malloc(sizeof(BTNode));
	**e = (s)->data[(s)->top];
	return true;
}

void InOrder(BTNode *b)   //�ǵݹ��������
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
		r = NULL;  //rָ��ոշ��ʹ��Ľڵ㣬��ʼΪ�� 
		flag = true;//Ϊ���ʾ���ڴ���ջ���ڵ� 
		while (!StackEmpty(st) && flag)
		{
			GetTop(st, &p);
			if (p->rchild == r)
			{
				printf("%c", p->data);
				Pop(&st, &p);
				r = p;
			}
			else if (r != NULL && p->rchild != NULL && p->rchild->data == r->data) //��ֹp->rchild��rӦ������ͬ�ĵ��ǵ�ַ��ͬ�����µ��ж����⡣
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


void destroy_tree(BTNode ** T) //��������
{
	if (*T)
	{
		//�ж��Ƿ���ڵ㣬���������ڵ�һֱ�ݹ���ȥ
		if ((*T)->lchild)
			destroy_tree(&((*T)->lchild));
		//�ж��Ƿ��ҽڵ㣬��������ҽڵ�һֱ�ݹ���ȥ
		if ((*T)->rchild)
			destroy_tree(&((*T)->rchild));

		//��һ�������������ҽ�㣬���˽��free��
		free(*T);
		*T = NULL;
	}
}