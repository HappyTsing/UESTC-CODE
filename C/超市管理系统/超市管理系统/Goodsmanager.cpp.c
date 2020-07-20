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

void info_init(void);						/*读入信息*/
void save_exit(void);						/*储存退出*/
void eatline(void);                         /*去除多余输入*/
            

void output_all(void);						/*显示全部信息*/
void info_change(void);						/*修改某个信息*/
void info_insert(void);						/*插入某个信息*/
void info_dele(void);						/*删除某个信息*/
void info_search(void);						/*查找某个信息*/
void info_sort(void);                       /*对商品价格进行排序*/
void info_deleteall(void);                  /*删除所有内容*/

void welcome_menu(void);					/*欢迎菜单*/
void exit_menu(void);						/*退出菜单*/

int main(void)
{
	int choice;
	welcome_menu();	info_init();
	printf("请输入你的选择：");
	scanf("%d", &choice);
	for (;;)
	{
		switch (choice)
		{
		case 1:/*显示所有商品的信息*/
			output_all();
			break;
		case 2:/*修改某个商品的信息*/
			info_change();
			break;
		case 3:/*插入某个商品的信息*/
			info_insert();
			break;
		case 4:/*删除某个商品的信息*/
			info_dele();
			break;
		case 5:/*查找某个商品的信息*/
			info_search();
			break;
		case 6:/*商品存盘并退出系统*/
		{
			exit_menu();
			save_exit();
			return 0;
		}
		case 7:/*对商品价格进行排序*/
			info_sort();
			break;

		case 8:/*删除所有内容*/
			info_deleteall();
			break;
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
void info_init(void)						/*读入信息*/
{
	FILE *fp;
	fp=fopen("Goodsinfo.txt", "rb");
	struct list *p;
	if (fp== NULL)
	{
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}

	for (;;)
	{
		
		new_item = malloc(sizeof(struct list));
		if (new_item == NULL)
		{
			perror("读入信息分配空间失败：");
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
void save_exit(void)    /*储存并推出*/
{
	FILE *fp;
	if (fgoods == NULL)
	{
		printf("列表空空如也");
			exit(EXIT_FAILURE);
	}

	fp = fopen("Goodsinfo.txt", "wb");
	if (fp == NULL)
	{
		printf("保存信息文件打开失败");
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
void output_all(void)  /*打印所有*/
{
	int n = 0;
	struct list *p;
		for (p = fgoods; p != NULL; p = p->next)
		{
			printf("\nID:%-10s名称:%-10s价格%-10d折扣:%-10.2f数量：%-10d剩余:%-10d", p->goods_id,p->goods_name,p->goods_price,p->goods_discount,p->goods_amount,p->goods_remain);
			n++;
	}
		printf("\n打印完毕!当前共有%d个商品\n\n",n);
}
void info_change(void)  /*修改某个商品*/
{
	int choice;
	char code[30];
	struct list *p;
	printf("\n根据商品ID修改：输入1\n根据商品名称修改：输入2\n退出修改：输入-1\n您的选择：");
	scanf("%d", &choice);
	if (choice == -1)
		return;
	else if (choice == 1) {
		printf("\n输入需要修改的商品ID\n退出修改：输入-1：\n");
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
			printf("未找到该ID商品，返回主菜单中...\n");
			return;
		}

	}
	else if (choice == 2) {
		printf("输入需要修改的商品名称:(退出查找：输入-1：)");
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
			printf("\n未找到该ID商品，返回主菜单中...\n");
			return;
		}
		
	}
	printf("\nID:%-10s名称:%-10s价格%-10d折扣:%-10.2f数量：%-10d剩余:%-10d", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
	printf("\n输入新的产品信息：\n");
	printf("商品ID：");
	scanf("%s", &p->goods_id);
	printf("\n商品名称：");
	scanf("%s", &p->goods_name);
	printf("\n商品价格：");
	scanf("%d", &p->goods_price);
	printf("\n商品折扣：");
	scanf("%f", &p->goods_discount);
	printf("\n商品数量：");
	scanf("%d", &p->goods_amount);
	printf("\n商品剩余：");
	scanf("%d", &p->goods_remain);
	for (;;)
	{
		if (p->goods_remain > p->goods_amount)
		{
			printf("\n错误！剩余数大于商品总数！请重新输入：");
			scanf("%d", &p->goods_remain);

		}
		else
			break;
	}
	printf("\n修改成功！修改后商品信息如下：\n");
	printf("ID:%-10s名称:%-10s价格%-10d折扣:%-10.2f数量：%-10d剩余:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
}
void info_insert(void)			/*插入某个信息*/
{
	struct list* new_good,*pre=NULL,*p;
	int choice,i;
	new_good = malloc(sizeof(struct list));
	printf("输入你要增加的商品信息：\n");
	printf("\n商品ID：");
	scanf("%s", &new_good->goods_id);
	for (p = fgoods;p!=NULL; p = p->next)
	{
		if (strcmp(new_good->goods_id, p->goods_id) == 0)
		{
			printf("\n该商品ID已存在！请重新输入：");
			scanf("%s", &new_good->goods_id);
			p = fgoods;

		}
	}
	printf("\n商品名称：");
	scanf("%s", &new_good->goods_name);
	for (p = fgoods; p != NULL; p = p->next)
	{
		if (strcmp(new_good->goods_name, p->goods_name) == 0)
		{
			printf("\n该商品名称已存在！请重新输入：");
			scanf("%s", &new_good->goods_name);
			p = fgoods;

		}
	}
	printf("\n商品价格：");
	scanf("%d", &new_good->goods_price);
	printf("\n商品折扣：");
	scanf("%f", &new_good->goods_discount);
	printf("\n商品数量：");
	scanf("%d", &new_good->goods_amount);
	printf("\n商品剩余：");
	scanf("%d", &new_good->goods_remain);
	for (;;)
	{
		if (new_good->goods_remain > new_good->goods_amount)
		{
			printf("错误！剩余数大于商品总数！请重新输入：");
			scanf("%d", &new_good->goods_remain);

		}
		else
			break;
	}
	printf("\n输入数字表明你要插入的位置：\n1：插入表头\n0：插入表尾\ni：插入第i号位\n您的选择：");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1: {
		new_good->next = fgoods;
		fgoods = new_good;
		printf("\n插入表头成功！返回主菜单中...\n");
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
		printf("插入表尾成功！返回主菜单中...\n");
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
			printf("插入第%d号位成功，返回主菜单中...\n", choice);
		
		}
		else
		{
			printf("插入位置超出范围，返回主菜单中...\n");
			return;
		}
	
	}break;
	}
}
void info_dele(void)					/*删除某个信息*/
	{   
		int choice;
		char code[30],sure;
		struct list *p,*pre;
		p = fgoods;
		pre = NULL;
		printf("根据商品ID删除：输入1\n根据商品名称删除：输入2\n退出删除：输入-1\n您的选择：");
		scanf("%d", &choice);
		if (choice == -1)
			return;
		else if (choice == 1) {
			printf("\n输入需要删除的商品ID\n退出查找：输入-1：\n");
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
				printf("未找到该ID商品，返回主菜单中...\n");
				return;
			}

		}
		else if (choice == 2) {
			printf("输入需要删除的商品名称:(退出删除：输入-1：)\n");
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
				printf("未找到该ID商品，返回主菜单中...\n");
				return;
			}

		}
		printf("ID:%-10s名称:%-10s价格%-10d折扣:%-10.2f数量：%-10d剩余:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
		printf("确认删除？是：Y否：N\n您的选择：");
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
			printf("\n删除成功！返回主菜单中...\n");
			return;
		}break;
		case 'N': {
			printf("\n取消删除成功！返回主菜单中...\n");
			return;
		}break;
		}
}
void info_search(void)                /*查找某个信息*/
{
	int choice;
	char code[30];
	struct list *p;
	printf("根据商品ID查找：输入1\n根据商品名称查找：输入2\n退出查找：输入-1\n您的选择：");
	scanf("%d", &choice);
	if (choice == -1)
		return;
	else if (choice == 1) {
		printf("\n输入需要查找的商品ID:(退出查找：输入-1：)");
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
			printf("\n未找到该ID商品，返回主菜单中...\n");
			return;
		}

	}
	else if (choice == 2) {
		printf("输入需要查找的商品名称:(退出查找：输入-1：)");
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
			printf("\n未找到该ID商品，返回主菜单中...\n");
			return;
		}

	}
	printf("\nID:%-10s名称:%-10s价格%-10d折扣:%-10.2f数量：%-10d剩余:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
}
void info_sort(void)            /*对商品价格进行排序*/
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
		printf("无商品\n");
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
		printf("排序完毕！\n");
	}break;
	}
	for (p = fgoods; p != NULL; p = p->next)
	{
		printf("ID:%-10s名称:%-10s价格%-10d折扣:%-10.2f数量：%-10d剩余:%-10d\n", p->goods_id, p->goods_name, p->goods_price, p->goods_discount, p->goods_amount, p->goods_remain);
		n++;
	}
	printf("当前共有%d个商品！\n", n);
}
void info_deleteall(void)                    /*删除所有内容*/
{
	char sure;
	struct list *p;
	printf("确认清空列表？是：Y否：N\n您的选择：");
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
		printf("\n删除成功！返回主菜单中...\n");

	}break;
	case 'N': {
		printf("\n取消删除成功！返回主菜单中...\n");
		return;
	}break;
	}
}
void welcome_menu(void)				/*欢迎菜单*/
{
	printf("*****************************************\n");
	printf("****** 欢迎使用超市商品信息储存系统 *****\n");
	printf("*****************************************\n");
	printf("*****************************************\n");
	printf("**************** 功能菜单 ***************\n");
	printf("*****************************************\n");
	printf(" 1：显示商品信息 \n");
	printf(" 2：商品信息修改 \n");
	printf(" 3：商品信息录入 \n");
	printf(" 4：商品信息删除 \n");
	printf(" 5：商品信息查找 \n");
	printf(" 6：存盘退出系统 \n");
	printf(" 7：商品信息排序 \n");
	printf(" 8：删除所有内容 \n");
}
void exit_menu(void)					/*退出菜单*/
{
	printf("*****************************************\n");
	printf("**************   正在退出   *************\n");
	printf("************** 感谢您的使用 *************\n");
	printf("*****************************************\n");
}
void eatline(void)
{
	while (getchar() != '\n')
		;
}