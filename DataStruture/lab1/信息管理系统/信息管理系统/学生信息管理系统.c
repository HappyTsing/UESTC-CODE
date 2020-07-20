#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
//����ṹ�����Ӧͷ�ļ�
typedef struct student	   	 //�������ݽ������-ѧ��
{
	char  sno[12];           //ѧ��
	char  sname[10];         //����
	char  sex[4];            //�Ա�
	char  major[20];         //רҵ
	struct student *next;	 //ָ�������ݽ��
} StudentList;
typedef struct stable        //����ѧ����
{
	int  rows;               //ѧ�����¼��
	int  cols;               //ѧ����Ϣ����
	StudentList *snode;      //ѧ����Ϣ���
} Stable;
Stable std_table;

typedef struct course         //�������ݽ������-�γ�
{
	char  cno[10];            //�γ̺�
	char  cname[20];          //�γ���
	int  classHours;          //��ʱ
	struct course *next;	  //ָ�������ݽ��
} CourseList;
typedef struct ctable         //����γ̱�
{
	int  rows;                //�γ̱��¼��
	int  cols;                //�γ���Ϣ����
	CourseList *cnode;        //�γ���Ϣ���
} Ctable;
Ctable cou_table;

typedef struct grade          //�������ݽ������
{
	char  sno[12];            //ѧ��
	char  cno[10];            //�γ̺�
	int  score;               //�ɼ�
	struct grade *next;	      //ָ�������ݽ��
} GradeList;
typedef struct gtable         //����ɼ���
{
	int  rows;                //�ɼ����¼��
	int  cols;                //�ɼ���Ϣ����
	GradeList *gnode;         //�ɼ���Ϣ���
} Gtable;
Gtable gra_table;


typedef struct stu_gra	  	  //�������ݽ������-ѧ���ɼ� 
{
	char  sno[12];            //ѧ��
	char  sname[10];          //����
	char  major[20];          //רҵ
	char  cname1[20];          //�γ���1
	int  score1;              //�ɼ�1
	char  cname2[20];          //�γ���2
	int  score2;              //�ɼ�2
	char  cname3[20];          //�γ���3
	int  score3;              //�ɼ�3
	struct stu_gra *next;	  //ָ�������ݽ��
} StudentgradeList;
typedef struct sgtable        //����ѧ���ɼ���ͷ 
{
	int  rows;               //ѧ�����¼��
	int  cols;               //ѧ����Ϣ����
	StudentgradeList *sgnode;      //ѧ����Ϣ���
} SGtable;
SGtable stdgra_table;


//����Ϊ��������
void list_create_student(void);
void list_create_course(void);
void list_create_grade(void);
void list_read_student(void);
void list_read_course(void);
void list_read_grade(void);
void output_student(void);
void output_course(void);
void output_grade(void);
//�����⺯��
void create_stdgra_table(void);
void save_sg_file(void);
void list_read_studentgrade(void);
void output_studentgrade(void);

//�ڰ��⺯��
void printf_course_grade(void);
StudentgradeList* MergeSort_studentgrade_C01(StudentgradeList* node);
StudentgradeList* MergeSort_studentgrade_C02(StudentgradeList* node);
StudentgradeList* MergeSort_studentgrade_C03(StudentgradeList* node);

//�ھ��⺯��
void printf_flunk_course(void);

//��ʮ�� ջ
typedef struct linknode	   	 //�������ݽ������-ѧ�� ջ
{
	char  sno[12];           //ѧ��
	char  sname[10];         //����
	char  sex[4];            //�Ա�
	char  major[20];         //רҵ
	struct linknode *next;	 //ָ�������ݽ��
} LinkStNode;
LinkStNode *stack_list;
Stable new_std_table;

void Stack(void); 
void InitStack(void); 
bool StackEmpty(void); 
void Push(StudentList *ps); 
StudentList * Pop(void);
void output_stack(void);

//��ʮһ�� ����
typedef struct
{
	StudentgradeList *front;
	StudentgradeList *rear;
}LinkQuNode;
LinkQuNode *queue_list;
void Queue(void);
void InitQueue(void);
bool QueueEmpty(void);
void enQueue(StudentgradeList *q);
bool deQueue(StudentgradeList **e);
void printf_queue(void);


//������
StudentList* MergeSort_student(StudentList* node);
CourseList* MergeSort_course(CourseList* node);
GradeList* MergeSort_grade(GradeList* node);


int main(void)
{
	int code;
	while (1) {
		printf("\n");
		puts("*****************************************************");
		puts("1. ����ѧ����Ϣ������");
		puts("2. ����γ���Ϣ������");
		puts("3. ����ɼ���Ϣ������");
		puts("4. ��ȡѧ����Ϣ��������ѧ������ĵ�������");
		puts("5. ��ȡ�γ���Ϣ���������γ̺�����ĵ�������");
		puts("6. ��ȡ�ɼ���Ϣ��������ѧ�źͿγ̺�����ĵ�������");
		puts("7. ��ȡ�ɼ���Ϣ����ѯ����ѧ�����пγ̵Ŀ��Գɼ�");
		puts("8. ��ȡ�ɼ���Ϣ����ѯ����ѧ��ָ���γ̵Ŀ��Գɼ�");
		puts("9. ��ȡ�ɼ���Ϣ����ѯָ���γ̳ɼ�С�� 60 �ֵ�ѧ��");
		puts("10. �� 4 �����ɵ�����ת��");
		puts("11. ����ʽ���н�� 7 �����⣻");
		puts("�������������ַ��˳�ϵͳ");
		puts("*****************************************************");
		scanf("%d", &code);
		switch (code)
		{
		case 1:	
			list_create_student(); //ÿ�����붼�������һ������
			break;
		case 2:
			list_create_course();  
			break;
		case 3:
			list_create_grade(); 
			break;
		case 4:
			list_read_student();
			MergeSort_student(std_table.snode);   	output_student();
			break;
		case 5:
			list_read_course();
			MergeSort_course(cou_table.cnode);	    output_course();
			break;
		case 6:
			list_read_grade();
			MergeSort_grade(gra_table.gnode);       output_grade();
			break;
		case 7:	
			list_read_student();
			MergeSort_student(std_table.snode);
			list_read_course();
			MergeSort_course(cou_table.cnode);		
			list_read_grade();
			MergeSort_grade(gra_table.gnode);
			create_stdgra_table();
			save_sg_file();
			list_read_studentgrade();		
			break;
		case 8:
			list_read_studentgrade();
			printf_course_grade();
			break;
		case 9:
			list_read_studentgrade();
			printf_flunk_course();
			break;
		case 10:
			 Stack();
			 output_stack();
			break;
		case 11:
			list_read_studentgrade();
			printf_queue();
				 break;
		default:
			return 0;
		}
	}

  	return 0;

}

//��ʼ�����б��������桢���������

void list_create_student(void)
{
	int i=1;
	FILE *fp_student;
	StudentList *std;
	std_table.cols = 10;
	std_table.rows = 4;
	std = (StudentList*)malloc(sizeof(StudentList));
	printf("�����%d��ѧ��", i);
	scanf("%s", std->sno);//�û�����
	printf("�����%d������", i);
	scanf("%s", std->sname);
	printf("�����%d���Ա�", i);
	scanf("%s", std->sex);
	printf("�����%d��רҵ", i);
	scanf("%s", std->major);
	std->next = NULL;
	std_table.snode = std;

	fp_student = fopen("student.dat", "w");
	if (fp_student == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}
	for (i = 2; i <= 10; i++)
	{
		std = (StudentList*)malloc(sizeof(StudentList));
		printf("�����%d��ѧ��", i);
		scanf("%s", std->sno);//�û�����
		printf("�����%d������", i);
		scanf("%s", std->sname);
		printf("�����%d���Ա�", i);
		scanf("%s", std->sex);
		printf("�����%d��רҵ", i);
		scanf("%s", std->major);
		std->next = std_table.snode;
		std_table.snode = std;
	}
		while (std_table.snode != NULL)
		{
			if (fwrite(std_table.snode, sizeof(StudentList), 1, fp_student) == 1)
				std_table.snode = std_table.snode->next;
		}
	fclose(fp_student);   	
}
void list_create_course(void) {
	
	int 	i = 1;
	FILE *fp_course;
	CourseList *course;
	cou_table.cols = 3;
	cou_table.rows = 3;
	course = (CourseList*)malloc(sizeof(CourseList));

	printf("�����%d���γ̺�", i);
	scanf("%s", course->cno);//�û�����
	printf("�����%d���γ���", i);
	scanf("%s", course->cname);
	printf("�����%d����ʱ", i);
	scanf("%d", &course->classHours);
	course->next = NULL;
	cou_table.cnode = course;

	fp_course = fopen("course.dat", "w");
	if (fp_course == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}
	for (i = 2; i <= 3; i++)
	{
		course = (CourseList*)malloc(sizeof(CourseList));
		printf("�����%d���γ̺�", i);
		scanf("%s", course->cno);//�û�����
		printf("�����%d���γ���", i);
		scanf("%s", course->cname);
		printf("�����%d����ʱ", i);
		scanf("%d", &course->classHours);
		course->next = cou_table.cnode;
		cou_table.cnode = course;
	}
	while (cou_table.cnode != NULL)
	{
		if (fwrite(cou_table.cnode, sizeof(CourseList), 1, fp_course) == 1)
			cou_table.cnode = cou_table.cnode->next;
	}
	fclose(fp_course);
}
void list_create_grade(void)
{
	int i = 1;
	FILE *fp_grade;
	GradeList *grade;
	gra_table.cols = 30;
	gra_table.rows = 3;
	i = 1;
	grade = (GradeList*)malloc(sizeof(GradeList));
	printf("�����%d��ѧ��", i);
	scanf("%s", grade->sno);//�û�����
	printf("�����%d���γ̺�", i);
	scanf("%s", grade->cno);
	printf("�����%d���ɼ�", i);
	scanf("%d", &grade->score);
	grade->next = NULL;
	gra_table.gnode = grade;

	fp_grade = fopen("courseGrade.dat", "w");
	if (fp_grade == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}
	for (i = 2; i <= 30; i++)
	{
		grade = (GradeList*)malloc(sizeof(GradeList));
		printf("�����%d��ѧ��", i);
		scanf("%s", grade->sno);//�û�����
		printf("�����%d���γ̺�", i);
		scanf("%s", grade->cno);
		printf("�����%d���ɼ�", i);
		scanf("%d", &grade->score);
		grade->next = gra_table.gnode;
		gra_table.gnode = grade;
	}
	while (gra_table.gnode != NULL)
	{
		if (fwrite(gra_table.gnode, sizeof(GradeList), 1, fp_grade) == 1)
			gra_table.gnode = gra_table.gnode->next;
	}
	fclose(fp_grade);
}
//��ȡ�ļ�
void list_read_student(void)					
{
	FILE *fp_student;
	StudentList * new_std;


	fp_student = fopen("student.dat", "rb");

	if (fp_student == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}

	std_table.snode = NULL;

	for (;;)
	{

		new_std= (StudentList*)malloc(sizeof(StudentList));
		if (new_std == NULL)
		{
			perror("������Ϣ����ռ�ʧ�ܣ�");
			exit(EXIT_FAILURE);
		}
		if (fread(new_std, sizeof(StudentList), 1, fp_student) == 1)
		{
			if (std_table.snode== NULL) {
				new_std->next = NULL;
				std_table.snode = new_std;
			}
			else {
		
				new_std->next = std_table.snode;
				std_table.snode = new_std;
			}
			
			
		}
		else
			break;
	}
	fclose(fp_student);
		
}   
void list_read_course(void)
{

	FILE *fp_course;
	CourseList * new_cou;


	fp_course = fopen("course.dat", "rb");

	if (fp_course == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}

	cou_table.cnode = NULL;

	for (;;)
	{

		new_cou = (CourseList*)malloc(sizeof(CourseList));
		if (new_cou == NULL)
		{
			perror("������Ϣ����ռ�ʧ�ܣ�");
			exit(EXIT_FAILURE);
		}
		if (fread(new_cou, sizeof(CourseList), 1, fp_course) == 1)
		{
			if (cou_table.cnode == NULL) {
				new_cou->next = NULL;
				cou_table.cnode = new_cou;
			}
			else {
				new_cou->next = cou_table.cnode;
				cou_table.cnode = new_cou;
			}
		}
		else
			break;
	}
	fclose(fp_course);
}
void list_read_grade(void)
{
	FILE *fp_grade;
	GradeList * new_gra;
	fp_grade = fopen("courseGrade.dat", "rb");
	if (fp_grade == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}
	gra_table.gnode = NULL;
	for (;;)
	{

		new_gra = (GradeList*)malloc(sizeof(GradeList));
		if (new_gra == NULL)
		{
			perror("������Ϣ����ռ�ʧ�ܣ�");
			exit(EXIT_FAILURE);
		}
		if (fread(new_gra, sizeof(GradeList), 1, fp_grade) == 1)
		{
			new_gra->next = gra_table.gnode;
			gra_table.gnode = new_gra;
		}
		else
			break;
	}
	fclose(fp_grade);
}
//���
void output_student(void)
{

	StudentList *p1;
	for (p1 = std_table.snode; p1 != NULL; p1 = p1->next)
	{
		printf("\nѧ��:%-10s����:%-10s�Ա�:%-10sרҵ:%-10s", p1->sno, p1->sname, p1->sex, p1->major);
	}

}
void output_course(void)
{

	CourseList *p2;
	for (p2 = cou_table.cnode; p2 != NULL; p2 = p2->next)
	{
		printf("\n�γ̺�:%-10s�γ���:%-10s��ʱ:%-10d", p2->cno, p2->cname, p2->classHours);
	}

}
void output_grade(void)
{

	GradeList *p3;
	for (p3 = gra_table.gnode; p3 != NULL; p3 = p3->next)
	{
		printf("\nѧ��:%-10s�γ̺�:%-10s�ɼ�:%-10d", p3->sno, p3->cno, p3->score);
	}

}
//�鲢����
StudentList* MergeSort_student(StudentList* node) {
	//���ж��������Ƿ����1��С��1ʱ��������
	if (node != NULL && node->next != NULL) {
		//���ÿ���ָ�룬�ҵ�������м�ڵ�
		StudentList *fast = node->next;
		StudentList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}
		//������ֳ������ֽ��зָ�
		StudentList *p1 = MergeSort_student(slow->next);
		slow->next = NULL;                 //�����˵�һ������Ľ�β
		StudentList *p2 = MergeSort_student(node);

		//�������������й鲢
		StudentList *p0 = (StudentList *)malloc(sizeof(StudentList));
		StudentList *p = p0;
		while (p1 != NULL && p2 != NULL) {
			if (strcmp(p1->sno, p2->sno) < 0) {
				p->next = p1;
				p1 = p1->next;
			}
			else {
				p->next = p2;
				p2 = p2->next;
			}
			p = p->next;
		}

		if (p1 != NULL) {
			p->next = p1;
		}

		if (p2 != NULL) {
			p->next = p2;
		}
		p = p0->next;
		free(p0);
		return p;
	}
	return node;
}
CourseList* MergeSort_course(CourseList* node) {
	//���ж��������Ƿ����1��С��1ʱ��������
	if (node != NULL && node->next != NULL) {
		//���ÿ���ָ�룬�ҵ�������м�ڵ�
		CourseList *fast = node->next;
		CourseList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//������ֳ������ֽ��зָ�
		CourseList *p1 = MergeSort_course(slow->next);
		slow->next = NULL;               
		CourseList *p2 = MergeSort_course(node);

		//�������������й鲢
		CourseList *p0 = (CourseList *)malloc(sizeof(CourseList));
		CourseList *p = p0;  //p0��Ϊͷָ�룬p�����ƶ�����
		                      
		while (p1 != NULL && p2 != NULL) {
			if (strcmp(p1->cno, p2->cno) < 0) {
				p->next = p1;
				p1 = p1->next;
			}
			else {
				p->next = p2;
				p2 = p2->next;
			}
			p = p->next;
		}

		if (p1 != NULL) {
			p->next = p1;
		}

		if (p2 != NULL) {
			p->next = p2;
		}

		p = p0->next;  //pָ��ͷָ����һ��λ�ã�����һ��������ݵ�λ�á�
		free(p0);
		return p;

	}

	return node;
}
GradeList* MergeSort_grade(GradeList* node) {
	//���ж��������Ƿ����1��С��1ʱ��������
	if (node != NULL && node->next != NULL) {
		//���ÿ���ָ�룬�ҵ�������м�ڵ�
		GradeList *fast = node->next;
		GradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//������ֳ������ֽ��зָ�
		GradeList *p1 = MergeSort_grade(slow->next);
		slow->next = NULL;           
		GradeList *p2 = MergeSort_grade(node);

		//�������������й鲢
		GradeList *p0 = (GradeList *)malloc(sizeof(GradeList));
		GradeList *p = p0;
		while (p1 != NULL && p2 != NULL) {
			if (strcmp(p1->sno, p2->sno) < 0) {
				p->next = p1;
				p1 = p1->next;
			}
			else if(strcmp(p1->sno, p2->sno)>0){
				p->next = p2;
				p2 = p2->next;
			}
			else {
				if (strcmp(p1->cno, p2->cno) < 0) {
					p->next = p1;
					p1 = p1->next;
				}
				else {
					p->next = p2;
					p2 = p2->next;
				}
				
			}

			p = p->next;
		}

		if (p1 != NULL) {
			p->next = p1;
		}

		if (p2 != NULL) {
			p->next = p2;
		}

		p = p0->next;
		free(p0);
		return p;

	}

	return node;
}

//����Ϊ������ĺ���
void create_stdgra_table(void)  //����ѧ���ɼ��� �����
{
	char cno[10];
	stdgra_table.sgnode = NULL;
	stdgra_table.cols = 5;
	stdgra_table.rows = 10;
	StudentList *ps = std_table.snode;
	CourseList  *pc = cou_table.cnode;
	GradeList   *pg = gra_table.gnode;
	StudentgradeList* new_sg;
    printf("\n�����ſγ�����ɼ�����:\n���ݿ⣺����C01\n���ݽṹ������C02\n������ƣ�����C03\n");
	scanf("%s", cno);

	
	while (ps != NULL&&pg!=NULL)
	{
		new_sg = (StudentgradeList*)malloc(sizeof(StudentgradeList));
		strcpy(new_sg->sno, ps->sno);
		strcpy(new_sg->sname, ps->sname);
		strcpy(new_sg->major, ps->major);
		    //����������Ŀ�ĳɼ�
		strcpy(new_sg->cname1, pc->cname);
		pc = pc->next;
		new_sg->score1 = pg->score;
		pg = pg->next;

		strcpy(new_sg->cname2, pc->cname);
		pc = pc->next;
		new_sg->score2 = pg->score;
		pg = pg->next;

		strcpy(new_sg->cname3, pc->cname);
		pc = cou_table.cnode; //��ʼ��pc
		new_sg->score3 = pg->score;
		pg = pg->next;
	
		ps = ps->next;
		//��������
		new_sg->next = stdgra_table.sgnode;
		stdgra_table.sgnode = new_sg;


		if (strcmp(cno, "C01") == 0)
		{
			//�����ݿ�ɼ�������
			stdgra_table.sgnode=MergeSort_studentgrade_C01(stdgra_table.sgnode);

		}
		else if (strcmp(cno, "C02") == 0)
		{
			//�����ݽṹ�ɼ�������
			stdgra_table.sgnode = MergeSort_studentgrade_C02(stdgra_table.sgnode);

		}
		else if (strcmp(cno, "C03") == 0)
		{
			//��������Ƴɼ�������
			stdgra_table.sgnode = MergeSort_studentgrade_C03(stdgra_table.sgnode);

		}
		
	}
	output_studentgrade();
}
void save_sg_file(void)//��ѧ���ɼ����ŵ��ļ���
{
	FILE *fp_sg;
	fp_sg = fopen("studentGrade.dat", "w");
	if (fp_sg == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}
	while (stdgra_table.sgnode != NULL)
	{
		if (fwrite(stdgra_table.sgnode, sizeof(StudentgradeList), 1, fp_sg) == 1)
			stdgra_table.sgnode = stdgra_table.sgnode->next;
	}

	fclose(fp_sg);

}
void list_read_studentgrade(void)  //���ļ��ж��� 
{

	FILE *fp_sg;
	StudentgradeList* new_sg;
	fp_sg = fopen("studentGrade.dat", "rb");

	if (fp_sg == NULL)
	{
		perror("������Ϣ�ļ���ʧ�ܣ�");
		exit(EXIT_FAILURE);
	}
	stdgra_table.sgnode = NULL;
	for (;;)
	{

		new_sg = (StudentgradeList*)malloc(sizeof(StudentgradeList));
		if (new_sg == NULL)
		{
			perror("������Ϣ����ռ�ʧ�ܣ�");
			exit(EXIT_FAILURE);
		}
		if (fread(new_sg, sizeof(StudentgradeList), 1, fp_sg) == 1)
		{
			new_sg->next = stdgra_table.sgnode;
			stdgra_table.sgnode = new_sg;

		}
		else
			break;
	}
	fclose(fp_sg);

}
void output_studentgrade(void)
{

	StudentgradeList *p;
	for (p = stdgra_table.sgnode; p != NULL; p = p->next)
	{
		printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", p->sno, p->sname, p->major);
		printf("\n%-10s:%-10d", p->cname1, p->score1);
		printf("\n%-10s:%-10d", p->cname2, p->score2);
		printf("\n%-10s:%-10d", p->cname3, p->score3);
	}

}

//����Ϊ�ڰ���ĺ���
void printf_course_grade(void) {
	char cno[10];
	StudentgradeList* p;
	printf("\n�������ѯ�γ̺�:\nC01\nC02\nC03\n");
	scanf("%s", cno);
	if (strcmp(cno, "C01") == 0)
	{
		//��CO1�ɼ�������
		p=MergeSort_studentgrade_C01(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
		    printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", p->sno, p->sname, p->major);
			printf("\n%-10s:%-10d", p->cname1, p->score1);
		}
	}
	else if (strcmp(cno, "C02") == 0)
	{
		//��CO2�ɼ�������
		p=MergeSort_studentgrade_C02(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", p->sno, p->sname, p->major);
			printf("\n%-10s:%-10d", p->cname2, p->score2);
		}
	}
	else if (strcmp(cno, "C03") == 0)
	{
		//��CO3�ɼ�������
		p=MergeSort_studentgrade_C03(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", p->sno, p->sname, p->major);
			printf("\n%-10s:%-10d", p->cname3, p->score3);
		}
	}
	else
	{
		printf("\nerror input");
		exit(1);
	}
}
StudentgradeList* MergeSort_studentgrade_C01(StudentgradeList* node) {
	//���ж��������Ƿ����1��С��1ʱ��������
	if (node != NULL && node->next != NULL) {
		//���ÿ���ָ�룬�ҵ�������м�ڵ�
		StudentgradeList *fast = node->next;
		StudentgradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//������ֳ������ֽ��зָ�
		StudentgradeList *p1 = MergeSort_studentgrade_C01(slow->next);
		slow->next = NULL;
		StudentgradeList *p2 = MergeSort_studentgrade_C01(node);

		//�������������й鲢
		StudentgradeList *p0 = (StudentgradeList *)malloc(sizeof(StudentgradeList));
		StudentgradeList *p = p0;  //p0��Ϊͷָ�룬p�����ƶ�����

		while (p1 != NULL && p2 != NULL) {
			if (p1->score1>p2->score1) {
				p->next = p1;
				p1 = p1->next;
			}
			else {
				p->next = p2;
				p2 = p2->next;
			}
			p = p->next;
		}

		if (p1 != NULL) {
			p->next = p1;
		}

		if (p2 != NULL) {
			p->next = p2;
		}

		p = p0->next;  //pָ��ͷָ����һ��λ�ã�����һ��������ݵ�λ�á�
		free(p0);
		return p;

	}

	return node;
}
StudentgradeList* MergeSort_studentgrade_C02(StudentgradeList* node) {
	//���ж��������Ƿ����1��С��1ʱ��������
	if (node != NULL && node->next != NULL) {
		//���ÿ���ָ�룬�ҵ�������м�ڵ�
		StudentgradeList *fast = node->next;
		StudentgradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//������ֳ������ֽ��зָ�
		StudentgradeList *p1 = MergeSort_studentgrade_C02(slow->next);
		slow->next = NULL;
		StudentgradeList *p2 = MergeSort_studentgrade_C02(node);

		//�������������й鲢
		StudentgradeList *p0 = (StudentgradeList *)malloc(sizeof(StudentgradeList));
		StudentgradeList *p = p0;  //p0��Ϊͷָ�룬p�����ƶ�����

		while (p1 != NULL && p2 != NULL) {
			if (p1->score2 > p2->score2) {
				p->next = p1;
				p1 = p1->next;
			}
			else {
				p->next = p2;
				p2 = p2->next;
			}
			p = p->next;
		}

		if (p1 != NULL) {
			p->next = p1;
		}

		if (p2 != NULL) {
			p->next = p2;
		}

		p = p0->next;  //pָ��ͷָ����һ��λ�ã�����һ��������ݵ�λ�á�
		free(p0);
		return p;

	}

	return node;
}
StudentgradeList* MergeSort_studentgrade_C03(StudentgradeList* node) {
	//���ж��������Ƿ����1��С��1ʱ��������
	if (node != NULL && node->next != NULL) {
		//���ÿ���ָ�룬�ҵ�������м�ڵ�
		StudentgradeList *fast = node->next;
		StudentgradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//������ֳ������ֽ��зָ�
		StudentgradeList *p1 = MergeSort_studentgrade_C03(slow->next);
		slow->next = NULL;
		StudentgradeList *p2 = MergeSort_studentgrade_C03(node);

		//�������������й鲢
		StudentgradeList *p0 = (StudentgradeList *)malloc(sizeof(StudentgradeList));
		StudentgradeList *p = p0;  //p0��Ϊͷָ�룬p�����ƶ�����

		while (p1 != NULL && p2 != NULL) {
			if (p1->score3 > p2->score3) {
				p->next = p1;
				p1 = p1->next;
			}
			else {
				p->next = p2;
				p2 = p2->next;
			}
			p = p->next;
		}

		if (p1 != NULL) {
			p->next = p1;
		}

		if (p2 != NULL) {
			p->next = p2;
		}

		p = p0->next;  //pָ��ͷָ����һ��λ�ã�����һ��������ݵ�λ�á�
		free(p0);
		return p;

	}

	return node;
}
//����Ϊ�ھ��⺯��
void printf_flunk_course(void) {
	char cno[10];
	StudentgradeList* p;
	printf("\n�������ѯ�γ̺�:\nC01\nC02\nC03\n");
	scanf("%s", cno);
	if (strcmp(cno, "C01") == 0)
	{
		//��CO1�ɼ�������
		p = MergeSort_studentgrade_C01(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			if (p->score1 < 60) {
				printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", p->sno, p->sname, p->major);
				printf("\n%-10s:%-10d", p->cname1, p->score1);
			}
	
		}
	}
	else if (strcmp(cno, "C02") == 0)
	{
		//��CO2�ɼ�������
		p = MergeSort_studentgrade_C02(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			if (p->score2 < 60) {
				printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", p->sno, p->sname, p->major);
				printf("\n%-10s:%-10d", p->cname2, p->score2);
			}
		}
	}
	else if (strcmp(cno, "C03") == 0)
	{
		//��CO3�ɼ�������
		p = MergeSort_studentgrade_C03(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			if (p->score3 < 60) {
				printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", p->sno, p->sname, p->major);
				printf("\n%-10s:%-10d", p->cname3, p->score3);
			}
		}
	}
	else
	{
		printf("\nerror input");
		exit(1);
	}

}
//��ʮ�� ջ
void Stack(void) {
	InitStack();
	StudentList *ps = std_table.snode;
	StudentList  *p;

	while (ps != NULL)
	{
		Push(ps);
		ps = ps->next;
	}

	new_std_table.snode = Pop();  //��һ����ջ
	p = new_std_table.snode;
	while ((p->next = Pop()) != NULL)
	{
		p = p->next;
	}
	p->next = NULL;
	
	
}
void InitStack(void) {
	stack_list= (LinkStNode*)malloc(sizeof(LinkStNode));
	stack_list->next = NULL;
}
bool StackEmpty(void) {
	return(stack_list->next == NULL);
}
void Push(StudentList *ps) {
	LinkStNode *p;
	p = (LinkStNode*)malloc(sizeof(LinkStNode));
	strcpy(p->sno, ps->sno);
	strcpy(p->sname, ps->sname);
	strcpy(p->sex, ps->sex);
	strcpy(p->major, ps->major);
	p->next = stack_list->next;
	stack_list -> next = p;

}
StudentList * Pop(void) {
	LinkStNode *p;
	StudentList * temp=NULL;
	temp = (StudentList *)malloc(sizeof(StudentList));
	if (StackEmpty())
		return NULL;
	p = stack_list->next;
	strcpy(temp->sno, p->sno);
	strcpy(temp->sname, p->sname);
	strcpy(temp->sex, p->sex);
	strcpy(temp->major, p->major);
    stack_list->next = p->next;
	return temp;

}
void output_stack(void)
{

	StudentList *p;
	for (p = new_std_table.snode; p != NULL; p = p->next)
	{
		printf("\nѧ��:%-10s����:%-10s�Ա�:%-10sרҵ:%-10s", p->sno, p->sname, p->sex, p->major);
	}

}
//��ʮһ�� ����

void Queue(StudentgradeList *Q)
{
	StudentgradeList *pq =Q;
	StudentgradeList *item;
	InitQueue();
	while (pq != NULL)
	{
		enQueue(pq);
		pq = pq->next;
	}
	while (deQueue(&item))
	{
		printf("\nѧ��:%-10s\n����:%-10s\nרҵ:%-10s", item->sno, item->sname, item->major);
		printf("\n%-10s:%-10d", item->cname1, item->score1);
		printf("\n%-10s:%-10d", item->cname2, item->score2);
		printf("\n%-10s:%-10d", item->cname3, item->score3);
	}
	return;
}
void InitQueue(void)
{
	queue_list = (LinkQuNode*)malloc(sizeof(LinkQuNode));
	queue_list->front = queue_list->rear = NULL;
}
bool QueueEmpty(void)
{
	return queue_list->rear == NULL;
}
void enQueue(StudentgradeList *q)
{
	StudentgradeList *p;
	p = (StudentgradeList*)malloc(sizeof(StudentgradeList));
	strcpy(p->sno, q->sno);
	strcpy(p->sname, q->sname);
	strcpy(p->major, q->major);
	strcpy(p->cname1, q->cname1);
	p->score1 = q->score1;
	strcpy(p->cname2, q->cname2);
	p->score2 = q->score2;
	strcpy(p->cname3, q->cname3);
	p->score3 = q->score3;


	p->next = NULL;
	if (QueueEmpty())
		queue_list->front = queue_list->rear = p;
	else
	{
		queue_list->rear->next = p;
		queue_list->rear = p;
	}
}
bool deQueue(StudentgradeList **e)
{
	StudentgradeList *t;
	if (QueueEmpty())
		return false;
	t = queue_list->front;
	if (queue_list->front == queue_list->rear)
		queue_list->front = queue_list->rear = NULL;
	else
		queue_list->front = queue_list->front->next;
	*e = t;
	return true;
}
void printf_queue(void) {
	char cno[10];
	StudentgradeList* p;
	printf("\n�������ѯ�γ̺�:\nC01\nC02\nC03\n");
	scanf("%s", cno);
	if (strcmp(cno, "C01") == 0)
	{
		//��CO1�ɼ�������
		p = MergeSort_studentgrade_C01(stdgra_table.sgnode);
		Queue(p);
	}
	else if (strcmp(cno, "C02") == 0)
	{
		//��CO2�ɼ�������
		p = MergeSort_studentgrade_C02(stdgra_table.sgnode);
		Queue(p);
	}
	else if (strcmp(cno, "C03") == 0)
	{
		//��CO3�ɼ�������
		p = MergeSort_studentgrade_C03(stdgra_table.sgnode);
		Queue(p);
	}
	else
	{
		printf("\nerror input");
		exit(1);
	}
}