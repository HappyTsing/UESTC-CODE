#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
//定义结构体和相应头文件
typedef struct student	   	 //定义数据结点类型-学生
{
	char  sno[12];           //学号
	char  sname[10];         //姓名
	char  sex[4];            //性别
	char  major[20];         //专业
	struct student *next;	 //指向后继数据结点
} StudentList;
typedef struct stable        //定义学生表
{
	int  rows;               //学生表记录数
	int  cols;               //学生信息列数
	StudentList *snode;      //学生信息结点
} Stable;
Stable std_table;

typedef struct course         //定义数据结点类型-课程
{
	char  cno[10];            //课程号
	char  cname[20];          //课程名
	int  classHours;          //课时
	struct course *next;	  //指向后继数据结点
} CourseList;
typedef struct ctable         //定义课程表
{
	int  rows;                //课程表记录数
	int  cols;                //课程信息列数
	CourseList *cnode;        //课程信息结点
} Ctable;
Ctable cou_table;

typedef struct grade          //定义数据结点类型
{
	char  sno[12];            //学号
	char  cno[10];            //课程号
	int  score;               //成绩
	struct grade *next;	      //指向后继数据结点
} GradeList;
typedef struct gtable         //定义成绩表
{
	int  rows;                //成绩表记录数
	int  cols;                //成绩信息列数
	GradeList *gnode;         //成绩信息结点
} Gtable;
Gtable gra_table;


typedef struct stu_gra	  	  //定义数据结点类型-学生成绩 
{
	char  sno[12];            //学号
	char  sname[10];          //姓名
	char  major[20];          //专业
	char  cname1[20];          //课程名1
	int  score1;              //成绩1
	char  cname2[20];          //课程名2
	int  score2;              //成绩2
	char  cname3[20];          //课程名3
	int  score3;              //成绩3
	struct stu_gra *next;	  //指向后继数据结点
} StudentgradeList;
typedef struct sgtable        //定义学生成绩表头 
{
	int  rows;               //学生表记录数
	int  cols;               //学生信息列数
	StudentgradeList *sgnode;      //学生信息结点
} SGtable;
SGtable stdgra_table;


//以下为函数定义
void list_create_student(void);
void list_create_course(void);
void list_create_grade(void);
void list_read_student(void);
void list_read_course(void);
void list_read_grade(void);
void output_student(void);
void output_course(void);
void output_grade(void);
//第七题函数
void create_stdgra_table(void);
void save_sg_file(void);
void list_read_studentgrade(void);
void output_studentgrade(void);

//第八题函数
void printf_course_grade(void);
StudentgradeList* MergeSort_studentgrade_C01(StudentgradeList* node);
StudentgradeList* MergeSort_studentgrade_C02(StudentgradeList* node);
StudentgradeList* MergeSort_studentgrade_C03(StudentgradeList* node);

//第九题函数
void printf_flunk_course(void);

//第十题 栈
typedef struct linknode	   	 //定义数据结点类型-学生 栈
{
	char  sno[12];           //学号
	char  sname[10];         //姓名
	char  sex[4];            //性别
	char  major[20];         //专业
	struct linknode *next;	 //指向后继数据结点
} LinkStNode;
LinkStNode *stack_list;
Stable new_std_table;

void Stack(void); 
void InitStack(void); 
bool StackEmpty(void); 
void Push(StudentList *ps); 
StudentList * Pop(void);
void output_stack(void);

//第十一题 队列
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


//排序函数
StudentList* MergeSort_student(StudentList* node);
CourseList* MergeSort_course(CourseList* node);
GradeList* MergeSort_grade(GradeList* node);


int main(void)
{
	int code;
	while (1) {
		printf("\n");
		puts("*****************************************************");
		puts("1. 输入学生信息并保存");
		puts("2. 输入课程信息并保存");
		puts("3. 输入成绩信息并保存");
		puts("4. 读取学生信息，创建按学号升序的单向链表");
		puts("5. 读取课程信息，创建按课程号升序的单向链表");
		puts("6. 读取成绩信息，创建按学号和课程号升序的单向链表");
		puts("7. 读取成绩信息，查询所有学生所有课程的考试成绩");
		puts("8. 读取成绩信息，查询所有学生指定课程的考试成绩");
		puts("9. 读取成绩信息，查询指定课程成绩小于 60 分的学生");
		puts("10. 将 4 中生成的链表反转；");
		puts("11. 用链式队列解决 7 的问题；");
		puts("输入任意其他字符退出系统");
		puts("*****************************************************");
		scanf("%d", &code);
		switch (code)
		{
		case 1:	
			list_create_student(); //每次输入都会替代上一次输入
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

//初始三个列表创建、保存、输出、排序

void list_create_student(void)
{
	int i=1;
	FILE *fp_student;
	StudentList *std;
	std_table.cols = 10;
	std_table.rows = 4;
	std = (StudentList*)malloc(sizeof(StudentList));
	printf("输入第%d个学号", i);
	scanf("%s", std->sno);//用户出入
	printf("输入第%d个姓名", i);
	scanf("%s", std->sname);
	printf("输入第%d个性别", i);
	scanf("%s", std->sex);
	printf("输入第%d个专业", i);
	scanf("%s", std->major);
	std->next = NULL;
	std_table.snode = std;

	fp_student = fopen("student.dat", "w");
	if (fp_student == NULL)
	{
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}
	for (i = 2; i <= 10; i++)
	{
		std = (StudentList*)malloc(sizeof(StudentList));
		printf("输入第%d个学号", i);
		scanf("%s", std->sno);//用户出入
		printf("输入第%d个姓名", i);
		scanf("%s", std->sname);
		printf("输入第%d个性别", i);
		scanf("%s", std->sex);
		printf("输入第%d个专业", i);
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

	printf("输入第%d个课程号", i);
	scanf("%s", course->cno);//用户出入
	printf("输入第%d个课程名", i);
	scanf("%s", course->cname);
	printf("输入第%d个课时", i);
	scanf("%d", &course->classHours);
	course->next = NULL;
	cou_table.cnode = course;

	fp_course = fopen("course.dat", "w");
	if (fp_course == NULL)
	{
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}
	for (i = 2; i <= 3; i++)
	{
		course = (CourseList*)malloc(sizeof(CourseList));
		printf("输入第%d个课程号", i);
		scanf("%s", course->cno);//用户出入
		printf("输入第%d个课程名", i);
		scanf("%s", course->cname);
		printf("输入第%d个课时", i);
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
	printf("输入第%d个学号", i);
	scanf("%s", grade->sno);//用户出入
	printf("输入第%d个课程号", i);
	scanf("%s", grade->cno);
	printf("输入第%d个成绩", i);
	scanf("%d", &grade->score);
	grade->next = NULL;
	gra_table.gnode = grade;

	fp_grade = fopen("courseGrade.dat", "w");
	if (fp_grade == NULL)
	{
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}
	for (i = 2; i <= 30; i++)
	{
		grade = (GradeList*)malloc(sizeof(GradeList));
		printf("输入第%d个学号", i);
		scanf("%s", grade->sno);//用户出入
		printf("输入第%d个课程号", i);
		scanf("%s", grade->cno);
		printf("输入第%d个成绩", i);
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
//读取文件
void list_read_student(void)					
{
	FILE *fp_student;
	StudentList * new_std;


	fp_student = fopen("student.dat", "rb");

	if (fp_student == NULL)
	{
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}

	std_table.snode = NULL;

	for (;;)
	{

		new_std= (StudentList*)malloc(sizeof(StudentList));
		if (new_std == NULL)
		{
			perror("读入信息分配空间失败：");
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
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}

	cou_table.cnode = NULL;

	for (;;)
	{

		new_cou = (CourseList*)malloc(sizeof(CourseList));
		if (new_cou == NULL)
		{
			perror("读入信息分配空间失败：");
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
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}
	gra_table.gnode = NULL;
	for (;;)
	{

		new_gra = (GradeList*)malloc(sizeof(GradeList));
		if (new_gra == NULL)
		{
			perror("读入信息分配空间失败：");
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
//输出
void output_student(void)
{

	StudentList *p1;
	for (p1 = std_table.snode; p1 != NULL; p1 = p1->next)
	{
		printf("\n学号:%-10s姓名:%-10s性别:%-10s专业:%-10s", p1->sno, p1->sname, p1->sex, p1->major);
	}

}
void output_course(void)
{

	CourseList *p2;
	for (p2 = cou_table.cnode; p2 != NULL; p2 = p2->next)
	{
		printf("\n课程号:%-10s课程名:%-10s课时:%-10d", p2->cno, p2->cname, p2->classHours);
	}

}
void output_grade(void)
{

	GradeList *p3;
	for (p3 = gra_table.gnode; p3 != NULL; p3 = p3->next)
	{
		printf("\n学号:%-10s课程号:%-10s成绩:%-10d", p3->sno, p3->cno, p3->score);
	}

}
//归并排序
StudentList* MergeSort_student(StudentList* node) {
	//先判断链表长度是否大于1，小于1时无须排序
	if (node != NULL && node->next != NULL) {
		//运用快慢指针，找到链表的中间节点
		StudentList *fast = node->next;
		StudentList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}
		//将链表分成两部分进行分割
		StudentList *p1 = MergeSort_student(slow->next);
		slow->next = NULL;                 //设置了第一个链表的结尾
		StudentList *p2 = MergeSort_student(node);

		//对两条子链进行归并
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
	//先判断链表长度是否大于1，小于1时无须排序
	if (node != NULL && node->next != NULL) {
		//运用快慢指针，找到链表的中间节点
		CourseList *fast = node->next;
		CourseList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//将链表分成两部分进行分割
		CourseList *p1 = MergeSort_course(slow->next);
		slow->next = NULL;               
		CourseList *p2 = MergeSort_course(node);

		//对两条子链进行归并
		CourseList *p0 = (CourseList *)malloc(sizeof(CourseList));
		CourseList *p = p0;  //p0作为头指针，p用于移动处理。
		                      
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

		p = p0->next;  //p指向头指针后第一个位置，即第一个存放数据的位置。
		free(p0);
		return p;

	}

	return node;
}
GradeList* MergeSort_grade(GradeList* node) {
	//先判断链表长度是否大于1，小于1时无须排序
	if (node != NULL && node->next != NULL) {
		//运用快慢指针，找到链表的中间节点
		GradeList *fast = node->next;
		GradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//将链表分成两部分进行分割
		GradeList *p1 = MergeSort_grade(slow->next);
		slow->next = NULL;           
		GradeList *p2 = MergeSort_grade(node);

		//对两条子链进行归并
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

//以下为第七题的函数
void create_stdgra_table(void)  //生成学生成绩表 并输出
{
	char cno[10];
	stdgra_table.sgnode = NULL;
	stdgra_table.cols = 5;
	stdgra_table.rows = 10;
	StudentList *ps = std_table.snode;
	CourseList  *pc = cou_table.cnode;
	GradeList   *pg = gra_table.gnode;
	StudentgradeList* new_sg;
    printf("\n按哪门课程排序成绩排序:\n数据库：输入C01\n数据结构：输入C02\n程序设计：输入C03\n");
	scanf("%s", cno);

	
	while (ps != NULL&&pg!=NULL)
	{
		new_sg = (StudentgradeList*)malloc(sizeof(StudentgradeList));
		strcpy(new_sg->sno, ps->sno);
		strcpy(new_sg->sname, ps->sname);
		strcpy(new_sg->major, ps->major);
		    //构建三个科目的成绩
		strcpy(new_sg->cname1, pc->cname);
		pc = pc->next;
		new_sg->score1 = pg->score;
		pg = pg->next;

		strcpy(new_sg->cname2, pc->cname);
		pc = pc->next;
		new_sg->score2 = pg->score;
		pg = pg->next;

		strcpy(new_sg->cname3, pc->cname);
		pc = cou_table.cnode; //初始化pc
		new_sg->score3 = pg->score;
		pg = pg->next;
	
		ps = ps->next;
		//构建链表
		new_sg->next = stdgra_table.sgnode;
		stdgra_table.sgnode = new_sg;


		if (strcmp(cno, "C01") == 0)
		{
			//按数据库成绩降序函数
			stdgra_table.sgnode=MergeSort_studentgrade_C01(stdgra_table.sgnode);

		}
		else if (strcmp(cno, "C02") == 0)
		{
			//按数据结构成绩降序函数
			stdgra_table.sgnode = MergeSort_studentgrade_C02(stdgra_table.sgnode);

		}
		else if (strcmp(cno, "C03") == 0)
		{
			//按程序设计成绩降序函数
			stdgra_table.sgnode = MergeSort_studentgrade_C03(stdgra_table.sgnode);

		}
		
	}
	output_studentgrade();
}
void save_sg_file(void)//将学生成绩表存放到文件中
{
	FILE *fp_sg;
	fp_sg = fopen("studentGrade.dat", "w");
	if (fp_sg == NULL)
	{
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}
	while (stdgra_table.sgnode != NULL)
	{
		if (fwrite(stdgra_table.sgnode, sizeof(StudentgradeList), 1, fp_sg) == 1)
			stdgra_table.sgnode = stdgra_table.sgnode->next;
	}

	fclose(fp_sg);

}
void list_read_studentgrade(void)  //从文件中读出 
{

	FILE *fp_sg;
	StudentgradeList* new_sg;
	fp_sg = fopen("studentGrade.dat", "rb");

	if (fp_sg == NULL)
	{
		perror("读入信息文件打开失败：");
		exit(EXIT_FAILURE);
	}
	stdgra_table.sgnode = NULL;
	for (;;)
	{

		new_sg = (StudentgradeList*)malloc(sizeof(StudentgradeList));
		if (new_sg == NULL)
		{
			perror("读入信息分配空间失败：");
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
		printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", p->sno, p->sname, p->major);
		printf("\n%-10s:%-10d", p->cname1, p->score1);
		printf("\n%-10s:%-10d", p->cname2, p->score2);
		printf("\n%-10s:%-10d", p->cname3, p->score3);
	}

}

//以下为第八题的函数
void printf_course_grade(void) {
	char cno[10];
	StudentgradeList* p;
	printf("\n请输入查询课程号:\nC01\nC02\nC03\n");
	scanf("%s", cno);
	if (strcmp(cno, "C01") == 0)
	{
		//按CO1成绩降序函数
		p=MergeSort_studentgrade_C01(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
		    printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", p->sno, p->sname, p->major);
			printf("\n%-10s:%-10d", p->cname1, p->score1);
		}
	}
	else if (strcmp(cno, "C02") == 0)
	{
		//按CO2成绩降序函数
		p=MergeSort_studentgrade_C02(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", p->sno, p->sname, p->major);
			printf("\n%-10s:%-10d", p->cname2, p->score2);
		}
	}
	else if (strcmp(cno, "C03") == 0)
	{
		//按CO3成绩降序函数
		p=MergeSort_studentgrade_C03(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", p->sno, p->sname, p->major);
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
	//先判断链表长度是否大于1，小于1时无须排序
	if (node != NULL && node->next != NULL) {
		//运用快慢指针，找到链表的中间节点
		StudentgradeList *fast = node->next;
		StudentgradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//将链表分成两部分进行分割
		StudentgradeList *p1 = MergeSort_studentgrade_C01(slow->next);
		slow->next = NULL;
		StudentgradeList *p2 = MergeSort_studentgrade_C01(node);

		//对两条子链进行归并
		StudentgradeList *p0 = (StudentgradeList *)malloc(sizeof(StudentgradeList));
		StudentgradeList *p = p0;  //p0作为头指针，p用于移动处理。

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

		p = p0->next;  //p指向头指针后第一个位置，即第一个存放数据的位置。
		free(p0);
		return p;

	}

	return node;
}
StudentgradeList* MergeSort_studentgrade_C02(StudentgradeList* node) {
	//先判断链表长度是否大于1，小于1时无须排序
	if (node != NULL && node->next != NULL) {
		//运用快慢指针，找到链表的中间节点
		StudentgradeList *fast = node->next;
		StudentgradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//将链表分成两部分进行分割
		StudentgradeList *p1 = MergeSort_studentgrade_C02(slow->next);
		slow->next = NULL;
		StudentgradeList *p2 = MergeSort_studentgrade_C02(node);

		//对两条子链进行归并
		StudentgradeList *p0 = (StudentgradeList *)malloc(sizeof(StudentgradeList));
		StudentgradeList *p = p0;  //p0作为头指针，p用于移动处理。

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

		p = p0->next;  //p指向头指针后第一个位置，即第一个存放数据的位置。
		free(p0);
		return p;

	}

	return node;
}
StudentgradeList* MergeSort_studentgrade_C03(StudentgradeList* node) {
	//先判断链表长度是否大于1，小于1时无须排序
	if (node != NULL && node->next != NULL) {
		//运用快慢指针，找到链表的中间节点
		StudentgradeList *fast = node->next;
		StudentgradeList *slow = node;
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}

		//将链表分成两部分进行分割
		StudentgradeList *p1 = MergeSort_studentgrade_C03(slow->next);
		slow->next = NULL;
		StudentgradeList *p2 = MergeSort_studentgrade_C03(node);

		//对两条子链进行归并
		StudentgradeList *p0 = (StudentgradeList *)malloc(sizeof(StudentgradeList));
		StudentgradeList *p = p0;  //p0作为头指针，p用于移动处理。

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

		p = p0->next;  //p指向头指针后第一个位置，即第一个存放数据的位置。
		free(p0);
		return p;

	}

	return node;
}
//以下为第九题函数
void printf_flunk_course(void) {
	char cno[10];
	StudentgradeList* p;
	printf("\n请输入查询课程号:\nC01\nC02\nC03\n");
	scanf("%s", cno);
	if (strcmp(cno, "C01") == 0)
	{
		//按CO1成绩降序函数
		p = MergeSort_studentgrade_C01(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			if (p->score1 < 60) {
				printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", p->sno, p->sname, p->major);
				printf("\n%-10s:%-10d", p->cname1, p->score1);
			}
	
		}
	}
	else if (strcmp(cno, "C02") == 0)
	{
		//按CO2成绩降序函数
		p = MergeSort_studentgrade_C02(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			if (p->score2 < 60) {
				printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", p->sno, p->sname, p->major);
				printf("\n%-10s:%-10d", p->cname2, p->score2);
			}
		}
	}
	else if (strcmp(cno, "C03") == 0)
	{
		//按CO3成绩降序函数
		p = MergeSort_studentgrade_C03(stdgra_table.sgnode);
		for (; p != NULL; p = p->next)
		{
			if (p->score3 < 60) {
				printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", p->sno, p->sname, p->major);
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
//第十题 栈
void Stack(void) {
	InitStack();
	StudentList *ps = std_table.snode;
	StudentList  *p;

	while (ps != NULL)
	{
		Push(ps);
		ps = ps->next;
	}

	new_std_table.snode = Pop();  //第一个出栈
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
		printf("\n学号:%-10s姓名:%-10s性别:%-10s专业:%-10s", p->sno, p->sname, p->sex, p->major);
	}

}
//第十一题 队列

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
		printf("\n学号:%-10s\n姓名:%-10s\n专业:%-10s", item->sno, item->sname, item->major);
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
	printf("\n请输入查询课程号:\nC01\nC02\nC03\n");
	scanf("%s", cno);
	if (strcmp(cno, "C01") == 0)
	{
		//按CO1成绩降序函数
		p = MergeSort_studentgrade_C01(stdgra_table.sgnode);
		Queue(p);
	}
	else if (strcmp(cno, "C02") == 0)
	{
		//按CO2成绩降序函数
		p = MergeSort_studentgrade_C02(stdgra_table.sgnode);
		Queue(p);
	}
	else if (strcmp(cno, "C03") == 0)
	{
		//按CO3成绩降序函数
		p = MergeSort_studentgrade_C03(stdgra_table.sgnode);
		Queue(p);
	}
	else
	{
		printf("\nerror input");
		exit(1);
	}
}