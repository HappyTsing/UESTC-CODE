#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>//Linux系统下的多线程遵循POSIX线程接口，称为pthread
#include <errno.h>
#include <unistd.h> //unistd.h是unix std的意思，是POSIX标准定义的unix类系统定义符号常量的头文件
#include <string.h>


pthread_mutex_t chopstick[5] ; //筷子作为mutex
pthread_t philosophers[5];  //5个哲学家
int philosophersNum[5] = {0, 1, 2, 3, 4};//代表5个哲学家的编号

void *eat_think(void *arg)
{
	int philoNum = *(int *)arg;
	int left=philoNum; //左筷子的编号和哲学家编号相同
	int right=(philoNum+1)%5 ;//右筷子的编号等于（哲学家编号+1）%5

	while(1){
		printf("哲学家%d正在思考问题\n",philoNum);
		usleep(3); //思考
		
		printf("哲学家%d准备吃东西\n",philoNum);
		
		pthread_mutex_lock(&chopstick[left]); //拿起左手的筷子
		printf("哲学家%d拿起筷子%d\n", philoNum, left);
		if (pthread_mutex_trylock(&chopstick[right]) == EBUSY){ //拿起右手的筷子	
			pthread_mutex_unlock(&chopstick[left]); //如果右边筷子被拿走放下左手的筷子
			printf("哲学家%d放下筷子%d\n", philoNum, left);
			continue;
		}
		printf("哲学家%d拿起筷子%d\n", philoNum, right);
		printf("哲学家%d正在吃东西\n",philoNum);
		usleep(3); //吃饭
		pthread_mutex_unlock(&chopstick[left]); //放下左手的筷子
		printf("哲学家%d放下筷子%d\n", philoNum, left);
		pthread_mutex_unlock(&chopstick[right]); //放下右手的筷子
		printf("哲学家%d放下筷子%d\n", philoNum, right);
		}
	
}
int main(){


	//信号量初始化
	int i;
	for (i = 0; i < 5; i++)
    pthread_mutex_init(&chopstick[i],NULL);

	//创建线程
	for(i=0;i<5;i++)
	pthread_create(&philosophers[i],NULL, eat_think, &philosophersNum[i]);

	//挂起线程
	for(i=0;i<5;i++)
	pthread_join(philosophers[i],NULL);
	
	//销毁互斥量
	for(i=0;i<5;i++)
	pthread_mutex_destroy(&chopstick[5]);

	return 0;
}
