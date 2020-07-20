#include<stdio.h>  //����ͷ�ڵ�ĵ�����
#include<stdlib.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}linknode;
//void InitList(linknode **pph);    ����Ҫ����ͷ�ڵ�ĳ�ʼ��
void DestroyList(linknode **pph);
bool ListEmpty(linknode *ph);
int ListLength(linknode*ph);
void DispList(linknode *ph);  //���������
bool GetElem(linknode *ph, int i, ElemType *e);
int LocateElem(linknode *ph, ElemType e);           //���ҵ���eһ��������ݣ�������Ӧ�ڵ��������򷵻�0
bool ListInsert(linknode **pph, int i, ElemType *e); //������e�����i��λ��
bool ListDelete(linknode **pph, int i, ElemType *e); //����i���ڵ�ɾ�������ýڵ�����ݼ�¼��e
void welcome_menu(void)
{
	printf("1:���������\n2:�ҵ���dataһ�������ݣ����ؽڵ���\n3:������data����iλ��\n4:ɾ����i��λ�ò���¼��data\n5:�õ���i��λ�õ�����\n6:���㳤��\n7:�п�\n8:�����б�\n");
}
int main(void)
{
	linknode *L=NULL;
	bool b;
	int choice,data,i,mem;
	//InitList(&L);   �˲�����Ҫ
	welcome_menu();
	printf("���������ѡ��");
	scanf("%d", &choice);
	for (;;)
	{
		switch (choice)
		{
		case 1:/*���������*/
			DispList(L);
			break;
		case 2:/*�ҵ���dataһ�������ݣ����ؽڵ���*/
			printf("data");
			scanf("%d", &data);
			mem = LocateElem(L, data);
			printf("%d", mem);
			break;
		case 3:/*������data����iλ��*/
			printf("data i");
			scanf("%d%d", &data, &i);
			b=ListInsert(&L, i, &data);
			printf("%d\n", b);
			break;
		case 4:/*ɾ����i��λ�ò���¼��data��*/
			printf("ɾ���ڼ������֣�");
			scanf("%d", &i);
			b=ListDelete(&L, i, &data);
			printf("data:%d bool:%d\n",data, b);
			break;
		case 5:/*�õ���i��λ�õ�����*/
			printf("�õ��ڼ���λ�ӵ����ݣ�");
			scanf("%d", &i);
			b=GetElem(L, i, &data);
			printf("%d\n", b);
			printf("%d\n", data);
			break;
		case 6:/*���㳤��*/
		{
			mem=ListLength(L);
			printf("%d", mem);
			break;
		}
		case 7:/*�п�*/
			b=ListEmpty(L);
			printf("bool:%d\n", b);

			break;

		case 8:/*�����б�*/
			DestroyList(&L);
			return 0;
		default:
		{
			printf("�Ƿ�ָ�");
			return 0;
		}
		}
		printf("���ٴ���������ѡ��");
		scanf("%d", &choice);
	}

}

/*void InitList(linknode **pph)
{
	*pph = (linknode*)malloc(sizeof(linknode));
	(*pph)->next = NULL;
}*/
void DestroyList(linknode **pph)
{
	if (*pph == NULL)  //ֻ��ͷָ������
	{
		free(*pph);
		return;
	}

	linknode *pre = *pph, *p = (*pph)->next;
	while (p)
	{
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
	return ;
}
bool ListEmpty(linknode *ph) //�շ����棬���򷵻ؼ�
{
	return(ph == NULL);
}
int ListLength(linknode*ph)
{
	int n=0;
	while (ph!=NULL)
	{
		n++;
		ph = ph->next;
	}

	return n;
}
void DispList(linknode *ph) //���������
{
	if (ListEmpty(ph))
	{
		printf("WU");
		return;
	}
	while (ph)
	{
		printf("%d\t", ph->data);
		ph = ph->next;
	}
	printf("\n");
}
bool GetElem(linknode *ph, int i, ElemType *e)    //����i���ڵ�����ݴ�ŵ�e��
{
	int n;
	if (i <= 0)
		return false;
	for (n = 1; n < i&&ph != NULL; n++)
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
int LocateElem(linknode *ph, ElemType e)          //���ҵ���eһ��������ݣ�������Ӧ�ڵ��������򷵻�0
{
	int n = 1;
	while (ph != NULL)
	{
		if (ph->data == e)
			return n;
		ph = ph->next;
		n++;
	}
	return 0;
}
bool ListInsert(linknode **pph, int i, ElemType *e)//������e�����i��λ��
{
	int n = 1;
	linknode *s, *phead = *pph;
	if (i <= 0)
		return false;
	if (i == 1)
	{
		s = (linknode*)malloc(sizeof(linknode));
		s->data = *e;
		s->next = *pph;
		*pph = s;
		return true;
	}

	while (phead != NULL && n < i - 1)
	{
		phead = phead->next;
		n++;
	}
	if (phead == NULL)
		return false;
	else
	{
		s = (linknode*)malloc(sizeof(linknode));
		s->data = *e;
		s->next = phead->next;
		phead->next = s;
		return true;
	}
}
bool ListDelete(linknode **pph, int i, ElemType *e)
{
	int n = 1;
	linknode *s,*phead=*pph;
	if (i<=0)
		return false;
	if (i == 1)
	{
		s = (*pph)->next;
		*e = s->data;
		*pph = s->next;
		free(s);
		return true;
	}
	while (phead != NULL && n < i - 1)
	{
		phead = phead->next;
		n++;
	}
	if (phead == NULL)
		return false;
	else
	{
		s = phead->next;
		if (s == NULL)
			return false;
		*e = s->data;
		phead->next = s->next;
		free(s);
		return true;
	}
}
