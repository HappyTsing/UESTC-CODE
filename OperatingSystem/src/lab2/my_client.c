#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512
struct msg_st
{
	long int msg_type;
	char text[MAX_TEXT];
};

int main()
{
	struct msg_st data_accept;//创建一个消息data
	struct msg_st data_send;//创建一个消息data
	char buffer[BUFSIZ];//BUFSIZ代表了默认的缓冲大小
	long int msgtype = 0; //返回消息队列中的第一个消息
	int msgid = -1;
	int pid;
	char pid_str[10]={0};


	//建立消息队列
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);//创建一个消息队列，读写权限是666（0代表是后面是8进制数）
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
while(1)
{
	//向消息队列中写消息，直到写入end
	pid=getpid();     //获取pid
	data_send.msg_type = 1;    //将消息data的类型设为1
	sprintf(pid_str,"%d",pid); //将数值型的pid转换为char*型的pid_str
	//strcat(buffer,pid_str);    //将pid_str加入缓冲的末尾
	strcpy(data_send.text, pid_str);  //把缓冲池中的内容复制给data.text 
	printf("向队列中发送的Client的pid是：%s\n",data_send.text);
		
	//向队列发送数据
	if(msgsnd(msgid, (void*)&data_send, MAX_TEXT, 0) == -1)
	{
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	
	//从队列中获取数据

	if(msgrcv(msgid, (void*)&data_accept, BUFSIZ, msgtype, 0) == -1)
	{
		fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	printf("从队列中获取的Server的pid是: %s\n",data_accept.text);	

}	
	//删除消息队列
	if(msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	

	exit(EXIT_SUCCESS);
}