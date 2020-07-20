#include<stdio.h>  //带头节点的单链表
#include<stdlib.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}linknode;
void InitList(linknode **pph);
void DestroyList(linknode **pph);
bool ListEmpty(linknode *ph);
int ListLength(linknode*ph);
void DispList(linknode *ph);  //输出整个表
bool GetElem(linknode *ph, int i, ElemType *e);
int LocateElem(linknode *ph, ElemType e);           //若找到和e一样大的数据，返回相应节点数，否则返回0
bool ListInsert(linknode *ph, int i, ElemType *e); //将数据e插入第i个位置
bool ListDelete(linknode *ph, int i, ElemType *e); //将第i个节点删除，将该节点的数据记录到e
void welcome_menu(void)
{
	printf("1:输出整个表\n2:找到和data一样的数据，返回节点数\n3:将数据data插入i位置\n4:删除第i个位置并记录到data\n5:得到第i个位置的数据\n6:计算长度\n7:判空\n8:毁灭列表\n");
}
int main(void)
{
	linknode *L;
	bool b;
	int choice,data,i,mem;
	InitList(&L);
	welcome_menu();
	printf("请输入你的选择：");
	scanf("%d", &choice);
	for (;;)
	{
		switch (choice)
		{
		case 1:/*输出整个表*/
			DispList(L);
			break;
		case 2:/*找到和data一样的数据，返回节点数*/
			printf("data");
			scanf("%d", &data);
			mem = LocateElem(L, data);
			printf("%d", mem);
			break;
		case 3:/*将数据data插入i位置*/
			printf("data i");
			scanf("%d%d", &data, &i);
			b=ListInsert(L, i, &data);
			printf("%d\n", b);
			break;
		case 4:/*删除第i个位置并记录到data中*/
			printf("删除第几个数字：");
			scanf("%d", &i);
			b=ListDelete(L, i, &data);
			printf("data:%d bool:%d\n",data, b);
			break;
		case 5:/*得到第i个位置的数据*/
			printf("得到第几个位子的数据：");
			scanf("%d", &i);
			b=GetElem(L, i, &data);
			printf("%d\n", b);
			printf("%d\n", data);
			break;
		case 6:/*计算长度*/
		{
			mem=ListLength(L);
			printf("%d", mem);
			break;
		}
		case 7:/*判空*/
			b=ListEmpty(L);
			printf("bool:%d\n", b);

			break;

		case 8:/*毁灭列表*/
			DestroyList(&L);
				return 0;
		default:
		{
			printf("非法指令！");
			return 0;
		}
		}
		printf("请再次输入您的选择：");
		scanf("%d", &choice);
	}

}

void InitList(linknode **pph)
{
	*pph = (linknode*)malloc(sizeof(linknode));
	(*pph)->next = NULL;
}
void DestroyList(linknode **pph)
{
	linknode *pre = *pph, *p = (*pph)->next;
	while (p)
	{
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);

}
bool ListEmpty(linknode *ph) //空返回真，否则返回假
{
	return(ph->next == NULL);
}
int ListLength(linknode*ph)
{
	int n=0;  //头节点为0，则首节点为1
	while (ph->next!=NULL)
	{
		n++;
		ph = ph->next;
	}

	return n;
}
void DispList(linknode *ph) //输出整个表
{
	if (ListEmpty(ph))
	{
		printf("WU");
		return;
	}
	ph = ph->next;  //ph一开始指向头节点
	while (ph)
	{
		printf("%d\t", ph->data);
		ph = ph->next;
	}
	printf("\n");
}
bool GetElem(linknode *ph, int i, ElemType *e)    //将第i个节点的数据存放到e中
{
	int n;
	for (n = 0; n < i&&ph != NULL; n++)
	{
		ph = ph->next;
	}
	if (ph == NULL)
		return false;
	else {
		*e = ph->data;
		return true;
	}
}
int LocateElem(linknode *ph, ElemType e)          //若找到和e一样大的数据，返回相应节点数，否则返回0
{
	int n = 1;
	ph = ph->next;
	while (ph != NULL)
	{
		if (ph->data == e)
			return n;
		ph = ph->next;
		n++;
	}
	return 0;
}
bool ListInsert(linknode *ph, int i, ElemType *e)//将数据e插入第i个位置
{
	int n = 0;
	linknode *s;
	while (ph != NULL && n < i - 1)
	{
		ph = ph->next;
		n++;
	}
	if (ph == NULL)
		return false;
	else
	{
		s = (linknode*)malloc(sizeof(linknode));
		s->data = *e;
		s->next = ph->next;
		ph->next = s;
		return true;
	}
}
bool ListDelete(linknode *ph, int i, ElemType *e)
{
	int n = 0;
	linknode *s;
	if (i<=0)
		return false;
	while (ph != NULL && n < i - 1)
	{
		ph = ph->next;
		n++;
	}
	if (ph == NULL)
		return false;
	else
	{
		s = ph->next;
		if (s == NULL)
			return false;
		*e = s->data;
		ph->next = s->next;
		free(s);
		return true;
	}
}
