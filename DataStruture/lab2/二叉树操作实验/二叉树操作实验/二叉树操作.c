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

//构建函数
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

//栈函数
bool GetTop(SqStack*s, BTNode** e);
void DestroyStack(SqStack **e);
bool Pop(SqStack**s, BTNode **e);
bool Push(SqStack**s, BTNode *e);
bool StackEmpty(SqStack *s);
void InitStack(SqStack **s);
//排序函数
void InOrder(BTNode *b);
void PostOrder(BTNode *b);
//销毁函数
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
	printf("中序遍历：");
	InOrder(B1);
	printf("后序遍历：");
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
	//top1++;  //top指向空区域
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
	//初始化第一个
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
			if (StackEmpty(st))  //空，入栈
			{
				Push(&st, b);
				my_tree = b;
			}
			else        //不空，判断方向是否是left，若是栈顶元素的左孩子等于第一步创建的节点，并将节点入栈
			{
				if (dir)
				{
					GetTop(st, &p);
					p->lchild = b;

				}
				else    //不是left，右孩子等于节点，删除栈顶，修改方向为left 入栈节点
				{
					GetTop(st, &p);
					p->rchild = b;
					Pop(&st, &p);
					dir = true;
				}
				Push(&st, b);  //节点入栈（两步合一）
			}
			top2++;
		}
		top2++;
		if (tree[top2] == '#')
		{
			if (!dir)    //方向右，出栈，方向左，改为方向右
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

void InOrder(BTNode *b)   //非递归中序遍历
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
			else if (r != NULL && p->rchild != NULL && p->rchild->data == r->data) //防止p->rchild和r应该是相同的但是地址不同所导致的判断问题。
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


void destroy_tree(BTNode ** T) //树的销毁
{
	if (*T)
	{
		//判断是否左节点，如果存在左节点一直递归下去
		if ((*T)->lchild)
			destroy_tree(&((*T)->lchild));
		//判断是否右节点，如果存在右节点一直递归下去
		if ((*T)->rchild)
			destroy_tree(&((*T)->rchild));

		//当一个结点无左结点和右结点，将此结点free掉
		free(*T);
		*T = NULL;
	}
}