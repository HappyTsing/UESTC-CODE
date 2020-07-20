#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_pro 3
#define N_con 4
#define M 10

//定义缓存区入区位置和出区位置
int in = 0;
int out = 0;

//定义缓存区
int buff[M] = {0};

//定义两个资源型信号量empty 和full，empty信号量表示当前空的缓冲区数量，full表示当前满的缓冲区数量。
sem_t empty;
sem_t full;

//定义互斥信号量mutex
pthread_mutex_t mutex;

int data;
FILE *fp;

void * product(void *arg)
{
    int producer_id =  *(int *)arg;
    while(1)
    {
		//模拟生产
	    sleep(1);
		
		//等待资源量，将empty-1，再与0比较大小，判断缓冲池是否有空
        sem_wait(&empty);
		
		//等待互斥量
        pthread_mutex_lock(&mutex);
		
		//从文件中取出内容

      if(fscanf(fp, "%d", &data)==EOF) 
        {
            fseek(fp, 0, SEEK_SET);//把文件指针fp指向文件的开头
            fscanf(fp, "%d", &data);
        }

	
        in = in % M;
        buff[in] = data;
		
        printf("生产者%d 在%d号缓冲区 放入产品%d\n", producer_id, in, buff[in]);
        in++;  //存入成功，入区位置+1
		
        pthread_mutex_unlock(&mutex);  //生产者停止使用缓存区
        sem_post(&full);  //full资源变量+1，表明缓存区中内容+1
    }
}


void *consume(void *arg)
{
    int consumer_id =  *(int *)arg;
    while(1)
    {
		//模拟消费
        sleep(1);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        out = out % M;
        printf("消费者%d 从%d号缓冲区 拿出产品%d\n", consumer_id, out, buff[out]);
        buff[out] = 0;  //取出后将原位置为0
        out++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

    }
}


int main()
{
	
    pthread_t producer[N_pro];   //生产者线程
    pthread_t consumer[N_con];   //消费者线程

    int i;
    int ret1[N_pro];
    int ret2[N_con];

	//初始化信号量
    int ini1 = sem_init(&empty, 0, M);
    int ini2 = sem_init(&full, 0, 0);
    if(ini1 || ini2 != 0)
    {
        printf("Sem初始化失败\n");
        exit(1);
    }

	//初始化互斥量
    int ini3 = pthread_mutex_init(&mutex, NULL);
    if(ini3 != 0 )
    {
        printf("mutex初始化失败\n");
        exit(1);
    }
	
	
    //以“只读”方式打开当前目录下的 data.txt 文件，并使文件指针fp 指向该文件
    fp = fopen("./data.txt", "r");
    if(fp == NULL)
	{
		printf("文件打开失败\n");
		exit(1);
	}

	//创建生产者线程
    for(i = 0; i < N_pro; i++)
    {
		int* id = malloc(sizeof(int));  //每次循坏为id分配一个地址空间，以免主线程切换后子线程还没有运行，造成线程名对应错误
		*id=i;
        ret1[i] = pthread_create(&producer[i], NULL, product, (void*)(id)); //传入生产者id
        if(ret1[i] != 0)
        {
            printf("生产者线程%d创建失败\n", i);
            exit(1);
        }
    }

	//创建消费者线程
    for(i = 0; i< N_con; i++)
    {
		int* id = malloc(sizeof(int));
		*id=i;
        ret2[i] = pthread_create(&consumer[i], NULL, consume,(void*)(id)); //传入消费者id
        if(ret2[i] != 0)
        {
            printf("消费者线程%d创建失败\n", i);
            exit(1);
        }
    }

	//挂起线程
    for(i = 0; i < N_pro; i++) 
	pthread_join(producer[i], NULL);

    for(i = 0; i < N_con; i++) 
	pthread_join(consumer[i], NULL);

	//销毁互斥量
	pthread_mutex_destroy(&mutex);
	
	//销毁信号量
	sem_destroy(&empty);
	sem_destroy(&full);
	
	return 0;


}
