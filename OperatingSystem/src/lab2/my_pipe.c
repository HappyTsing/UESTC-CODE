#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main( )
{ 
	pid_t pid1,pid2;
	int pipe_fd[2];
	char *msg1="child 1 process is sending message!";
	char *msg2="child 2 process is sending message!";
	char buf[100];
	/*创建一个管道*/
	if(pipe(pipe_fd)<0)
	{
		printf("pipe create error\n");
		return -1;
	}
	
	/*创建子进程*/
	if((pid1=fork( ))==0)	// 子进程1执行序列
	  {
		close(pipe_fd[0]);	// 子进程先关闭管道的读段
		write(pipe_fd[1],msg1,strlen(msg1));     //向管道写长为strlen(msg1)字节的串
		exit(0);
	   } 
	 else if(pid1>0)	    // 父进程执行序列
	  {
		waitpid(pid1,NULL,0);	// 同步1--等子进程1先写完		
		if((pid2=fork( ))==0)	// 子进程2执行序列
		{ 
			close(pipe_fd[0]);	// 子进程先关闭管道的读段
			write(pipe_fd[1],msg2,strlen(msg2)); //向管道写长为strlen(msg2)字节的串
			exit(0);
		 }
		 else if(pid2>0)	    // 父进程执行序列
		 {  			
			waitpid(pid2,NULL,0);	// 同步2--再等子进程2写完
			close(pipe_fd[1]);	    // 父进程先关闭管道的写段
			if(read(pipe_fd[0],buf,strlen(msg1))>0)   //读出msg1
				printf("%s\n",buf);
			if(read(pipe_fd[0],buf,strlen(msg2))>0)   //读出msg2
				printf("%s\n",buf);
			exit(0);
		}
	  }
	  return 0;
}


