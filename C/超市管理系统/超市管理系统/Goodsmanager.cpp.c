#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 100;
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30

struct list {
	char	goods_id[MAX_ID_LEN];
	char	goods_name[MAX_NAME_LEN];
	int  	goods_price;
	float	goods_discount;
	int		goods_amount;
	int		goods_remain;
	struct list *next;
};
struct list *fgoods=NULL;
struct list* new_item;

void info_init(void);						/*������Ϣ*/
void save_exit(void);						/*�����˳�*/
void eatline(void);                         /*ȥ����������*/
            

void output_all(void);						/*��ʾȫ����Ϣ*/
void info_change(void);						/*�޸�ĳ����Ϣ*/
void info_insert(void);						/*����ĳ����Ϣ*/
void info_dele(void);						/*ɾ��ĳ����Ϣ*/
void info_search(void);						/*����ĳ����Ϣ*/
void info_sort(void);                       /*����Ʒ�۸��������*/
void info_deleteall(void);                  /*ɾ����������*/

void welcome_menu(void);					/*��ӭ�˵�*/
void exit_menu(void);						/*�˳��˵�*/

int main(void)
{
	int choice;
	welcome_menu();	info_init();
	printf("���������ѡ��");
	scanf("%d", &choice);
	for (;;)
	{
		switch (choice)
		{
		case 1:/*��ʾ������Ʒ����Ϣ*/
			output_all();
			break;
		case 2:/*�޸�ĳ����Ʒ����Ϣ*/
			info_change();
			break;
		case 3:/*����ĳ����Ʒ����Ϣ*/
			info_insert();
			break;
		case 4:/*ɾ��ĳ����Ʒ����Ϣ*/
			info_dele();
			break;
		case 5:/*����ĳ����Ʒ����Ϣ*/
			info_search();
			break;
		case 6:/*��Ʒ���̲��˳�ϵͳ*/
		{
			exit_menu();
			save_exit();
			return 0;
		}
		case 7:/*����Ʒ�۸��������*/
			info_sort();
			break;

		case 8:/*ɾ����������*/
			info_deleteall();
			break;
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
void info_init(void)						/*������Ϣ*/
{
	FILE *fp;
	fp=fopen("Goodsinfo.txt", "rb");
	struct list *p;
	if (fp== NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}

	for (;;)
	{
		
		new_item = malloc(sizeof(struct list));
		if (new_item == NULL)
		{
			perror("������Ϣ����ռ�ʧ�ܣ�");
			exit(EXIT_FAILURE);
		}
		if (fread(new_item, sizeof(struct list), 1, fp) == 1)
		{
			p = fgoods;
			if (p == NULL) {
				new_item->next = NULL;
				fgoods = new_item;
			}
			else
			{
				for (p = fgoods; p->next != NULL; p = p->next)
					;
				new_item->next = p->next;
				p->next = new_item;
			}
		}
		else
			break;
	}
	fclose(fp);
}
void save_exit(void)    /*���沢�Ƴ�*/
{
	FILE *fp;
	if (fgoods == NULL)
	{
		printf("�б�տ���Ҳ");
			exit(EXIT_FAILURE);
	}

	fp = fopen("Goodsinfo.txt", "wb");
	if (fp == NULL)
	{
		printf("������Ϣ�ļ���ʧ��");
			exit(EXIT_FAILURE);
	}
	while (fgoods != NULL)
	{
		if (fwrite(fgoods, sizeof(struct list), 1, fp) == 1)
			fgoods = fgoods->next;
	}
	fclose(fp);
	exit(EXIT_SUCCESS);

}
void output_all(void)  /*��ӡ����*/
{
	int n = 0;
	struct list *p;
		for (p = fgoods; p != NULL; p = p->next)
		{
			printf("\nID:%-10s����:%-10s�۸�%-10d�ۿ�:%-10.2f������%-10dʣ��:%-10d", p->goods_id,p->goods_name,p->goods_price,p->goods_discount,p->goods_amount,p->goods_remain);
			n++;
	}
		printf("\n��ӡ���!��ǰ����%d����Ʒ\n\n",n);
}
void info_change(void)  /*�޸�ĳ����Ʒ*/
{
	int choice;
	char code[30];
	struct list *p;
	printf("\n������ƷID�޸ģ�����1\n������Ʒ�����޸ģ�����2\n�˳��޸ģ�����-1\n����ѡ��");
	scanf("%d", &choice);
	if (choice == -1)
		return;
	else if (choice == 1) {
		printf("\n������Ҫ�޸ĵ���ƷID\n�˳��޸ģ�����-1��\n");
		scanf("%s", code);
		if(strcmp(code,"-1")==0)
			return ;
		for (p = fgoods; p!=NULL; p = p->next)
		{
			if (strcmp(p->goods_id, code) == 0)
				break;
		}
		if (p == NULL)
		{
			printf("δ�ҵ���ID��Ʒ���������˵���...\n");
			return;
		}

	}
	else if (choice == 2) {
		printf("������Ҫ�޸ĵ���Ʒ����:(�˳����ң�����-1��)");
		scanf("%s", code);
		if (strcmp(code, "-1") == 0)
			return;
		for (p = fgoods; p!=NULL; p = p->next)
		{
			if (strcmp(p->goods_name, code) == 0)
				break;
		}
		if (p == NULL)
		{
			printf("\nδ�ҵ���ID��Ʒ���������˵���...\n");
			return;
		}
		
	}
	printf("\nID:%-10s����:%-10s�۸�%-10d�ۿ�:%-10.2f������%-10dʣ��:%-10d", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
	printf("\n�����µĲ�Ʒ��Ϣ��\n");
	printf("��ƷID��");
	scanf("%s", &p->goods_id);
	printf("\n��Ʒ���ƣ�");
	scanf("%s", &p->goods_name);
	printf("\n��Ʒ�۸�");
	scanf("%d", &p->goods_price);
	printf("\n��Ʒ�ۿۣ�");
	scanf("%f", &p->goods_discount);
	printf("\n��Ʒ������");
	scanf("%d", &p->goods_amount);
	printf("\n��Ʒʣ�ࣺ");
	scanf("%d", &p->goods_remain);
	for (;;)
	{
		if (p->goods_remain > p->goods_amount)
		{
			printf("\n����ʣ����������Ʒ���������������룺");
			scanf("%d", &p->goods_remain);

		}
		else
			break;
	}
	printf("\n�޸ĳɹ����޸ĺ���Ʒ��Ϣ���£�\n");
	printf("ID:%-10s����:%-10s�۸�%-10d�ۿ�:%-10.2f������%-10dʣ��:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
}
void info_insert(void)			/*����ĳ����Ϣ*/
{
	struct list* new_good,*pre=NULL,*p;
	int choice,i;
	new_good = malloc(sizeof(struct list));
	printf("������Ҫ���ӵ���Ʒ��Ϣ��\n");
	printf("\n��ƷID��");
	scanf("%s", &new_good->goods_id);
	for (p = fgoods;p!=NULL; p = p->next)
	{
		if (strcmp(new_good->goods_id, p->goods_id) == 0)
		{
			printf("\n����ƷID�Ѵ��ڣ����������룺");
			scanf("%s", &new_good->goods_id);
			p = fgoods;

		}
	}
	printf("\n��Ʒ���ƣ�");
	scanf("%s", &new_good->goods_name);
	for (p = fgoods; p != NULL; p = p->next)
	{
		if (strcmp(new_good->goods_name, p->goods_name) == 0)
		{
			printf("\n����Ʒ�����Ѵ��ڣ����������룺");
			scanf("%s", &new_good->goods_name);
			p = fgoods;

		}
	}
	printf("\n��Ʒ�۸�");
	scanf("%d", &new_good->goods_price);
	printf("\n��Ʒ�ۿۣ�");
	scanf("%f", &new_good->goods_discount);
	printf("\n��Ʒ������");
	scanf("%d", &new_good->goods_amount);
	printf("\n��Ʒʣ�ࣺ");
	scanf("%d", &new_good->goods_remain);
	for (;;)
	{
		if (new_good->goods_remain > new_good->goods_amount)
		{
			printf("����ʣ����������Ʒ���������������룺");
			scanf("%d", &new_good->goods_remain);

		}
		else
			break;
	}
	printf("\n�������ֱ�����Ҫ�����λ�ã�\n1�������ͷ\n0�������β\ni�������i��λ\n����ѡ��");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1: {
		new_good->next = fgoods;
		fgoods = new_good;
		printf("\n�����ͷ�ɹ����������˵���...\n");
	}break;
	case 0: {
		p = fgoods;
		if (p == NULL){
			new_good->next = NULL;
		    fgoods = new_good; }
		else
		{
			for (p = fgoods; p->next != NULL; p = p->next)
				;
			new_good->next = NULL;
			p->next = new_good;
		}
		printf("�����β�ɹ����������˵���...\n");
	}break;
	default: {
		p = fgoods;
		for (i = 1; i < choice&&p->next!=NULL; i++)
		{
			pre = p;
			p = p->next;
		}
		if (p != NULL&&pre!=NULL)
		{
			pre->next = new_good;
			new_good->next = p;
			printf("�����%d��λ�ɹ����������˵���...\n", choice);
		
		}
		else
		{
			printf("����λ�ó�����Χ���������˵���...\n");
			return;
		}
	
	}break;
	}
}
void info_dele(void)					/*ɾ��ĳ����Ϣ*/
	{   
		int choice;
		char code[30],sure;
		struct list *p,*pre;
		p = fgoods;
		pre = NULL;
		printf("������ƷIDɾ��������1\n������Ʒ����ɾ��������2\n�˳�ɾ��������-1\n����ѡ��");
		scanf("%d", &choice);
		if (choice == -1)
			return;
		else if (choice == 1) {
			printf("\n������Ҫɾ������ƷID\n�˳����ң�����-1��\n");
			scanf("%s", code);
			if (strcmp(code, "-1") == 0)
				return;
			for (pre=NULL; p!=NULL; pre=p,p = p->next)
			{
				if (strcmp(p->goods_id, code) == 0)
					break;
			}
			if (p == NULL)
			{
				printf("δ�ҵ���ID��Ʒ���������˵���...\n");
				return;
			}

		}
		else if (choice == 2) {
			printf("������Ҫɾ������Ʒ����:(�˳�ɾ��������-1��)\n");
			scanf("%s", code);
			if (strcmp(code, "-1") == 0)
				return;
			for (pre=NULL; p!=NULL; pre=p,p= p->next)
			{
				if (strcmp(p->goods_name, code) == 0)
					break;
			}
			if (p == NULL)
			{
				printf("δ�ҵ���ID��Ʒ���������˵���...\n");
				return;
			}

		}
		printf("ID:%-10s����:%-10s�۸�%-10d�ۿ�:%-10.2f������%-10dʣ��:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
		printf("ȷ��ɾ�����ǣ�Y��N\n����ѡ��");
		eatline();
		scanf("%c", &sure);
		sure = toupper(sure);
		switch (sure)
		{
		case 'Y': {
			if (pre == NULL)
				fgoods = fgoods->next;
			else
				pre->next = p->next;
			free(p);
			printf("\nɾ���ɹ����������˵���...\n");
			return;
		}break;
		case 'N': {
			printf("\nȡ��ɾ���ɹ����������˵���...\n");
			return;
		}break;
		}
}
void info_search(void)                /*����ĳ����Ϣ*/
{
	int choice;
	char code[30];
	struct list *p;
	printf("������ƷID���ң�����1\n������Ʒ���Ʋ��ң�����2\n�˳����ң�����-1\n����ѡ��");
	scanf("%d", &choice);
	if (choice == -1)
		return;
	else if (choice == 1) {
		printf("\n������Ҫ���ҵ���ƷID:(�˳����ң�����-1��)");
		scanf("%s", code);
		if (strcmp(code, "-1") == 0)
			return;
		for (p = fgoods; p != NULL; p = p->next)
		{
			if (strcmp(p->goods_id, code) == 0)
				break;
		}
		if (p == NULL)
		{
			printf("\nδ�ҵ���ID��Ʒ���������˵���...\n");
			return;
		}

	}
	else if (choice == 2) {
		printf("������Ҫ���ҵ���Ʒ����:(�˳����ң�����-1��)");
		scanf("%s", code);
		if (strcmp(code, "-1") == 0)
			return;
		for (p = fgoods; p != NULL; p = p->next)
		{
			if (strcmp(p->goods_name, code) == 0)
				break;
		}
		if (p == NULL)
		{
			printf("\nδ�ҵ���ID��Ʒ���������˵���...\n");
			return;
		}

	}
	printf("\nID:%-10s����:%-10s�۸�%-10d�ۿ�:%-10.2f������%-10dʣ��:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
}
void info_sort(void)            /*����Ʒ�۸��������*/
{
	struct list *p, *first, *second,*temp;;
	int num = 0,i,j,n=0;
	p = fgoods;
	while (p != NULL)
	{
		num++;
		p = p->next;
	}
	switch (num)
	{
	case 0:
	{
		printf("����Ʒ\n");
		return;
	}break;
	default:
	{

		for (i = 1; i < num; i++)
		{
			first = fgoods;
			second = fgoods->next;
			for (j = 0; j < num - i; j++)
			{
				if (first->goods_price > second->goods_price)
				{
					temp = malloc(sizeof(struct list));
					*temp = *first;
					strcpy(first->goods_id, second->goods_id);
					strcpy(first->goods_name, second->goods_name);
					first->goods_amount = second->goods_amount;
					first->goods_discount = second->goods_discount;
					first->goods_price = second->goods_price;
					first->goods_remain = second->goods_remain;

					strcpy(second->goods_id, temp->goods_id);
					strcpy(second->goods_name, temp->goods_name);
					second->goods_amount = temp->goods_amount;
					second->goods_discount = temp->goods_discount;
					second->goods_price = temp->goods_price;
					second->goods_remain = temp->goods_remain;
					free(temp);
				}
				first = first->next;
				second = second->next;
			}
		}
		printf("������ϣ�\n");
	}break;
	}
	for (p = fgoods; p != NULL; p = p->next)
	{
		printf("ID:%-10s����:%-10s�۸�%-10d�ۿ�:%-10.2f������%-10dʣ��:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
		n++;
	}
	printf("��ǰ����%d����Ʒ��\n", n);
}
void info_deleteall(void)                    /*ɾ����������*/
{
	char sure;
	struct list *p;
	printf("ȷ������б��ǣ�Y��N\n����ѡ��");
	scanf("%c", &sure);
	sure = toupper(sure);
	switch (sure)
	{
	case 'Y': {
		while(fgoods!=NULL)
		{
			p = fgoods;
			fgoods = fgoods->next;
			free(p);
			
		}
		printf("\nɾ���ɹ����������˵���...\n");

	}break;
	case 'N': {
		printf("\nȡ��ɾ���ɹ����������˵���...\n");
		return;
	}break;
	}
}
void welcome_menu(void)				/*��ӭ�˵�*/
{
	printf("*****************************************\n");
	printf("****** ��ӭʹ�ó�����Ʒ��Ϣ����ϵͳ *****\n");
	printf("*****************************************\n");
	printf("*****************************************\n");
	printf("**************** ���ܲ˵� ***************\n");
	printf("*****************************************\n");
	printf(" 1����ʾ��Ʒ��Ϣ \n");
	printf(" 2����Ʒ��Ϣ�޸� \n");
	printf(" 3����Ʒ��Ϣ¼�� \n");
	printf(" 4����Ʒ��Ϣɾ�� \n");
	printf(" 5����Ʒ��Ϣ���� \n");
	printf(" 6�������˳�ϵͳ \n");
	printf(" 7����Ʒ��Ϣ���� \n");
	printf(" 8��ɾ���������� \n");
}
void exit_menu(void)					/*�˳��˵�*/
{
	printf("*****************************************\n");
	printf("**************   �����˳�   *************\n");
	printf("************** ��л����ʹ�� *************\n");
	printf("*****************************************\n");
}
void eatline(void)
{
	while (getchar() != '\n')
		;
}