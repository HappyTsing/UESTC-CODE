
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#define MAX_CMD_STR 100

void sig_pipe(int signo) {	
	printf("[cli] SIGPIPE is coming!\n");
}

int echo_rqt(int sockfd)
{
	int len_h=0;  //主机字节序
	int len_n=0;  //网络字节序
	int res;   
	int sign=0;  //三个取值：0 1 2，0表示初次读取，输出[echo_rep] ，1表示读取完毕，输出换行符，2表示循环读取，不输出换行符。
	
    char buf[MAX_CMD_STR+1];
    while (fgets(buf, MAX_CMD_STR, stdin)) {
		//收到exit，退出循环，返回
		if(strncmp(buf, "exit", 4) == 0){
			return 0;
		}
		int len = strnlen(buf, MAX_CMD_STR);
		//查询所读取一行字符的长度，并将行末\n更换为\0
		if(buf[len-1] == '\n')	// If only '\n' input, '\0' will be send out;
			buf[len-1] = 0;
		/*else
		{
			len = strnlen(buf,200);
			buf[len-1] = 0;
		}*/
		//先发数据长度，再发缓存数据
		len_n=htonl(len);
        write(sockfd, &len_n, sizeof(len_n));
        write(sockfd, buf, len);
	
        memset(buf, 0, sizeof(buf));
		
		
		//循环回显数据，先读长度，再读数据	
		res=read(sockfd, &len, sizeof(len));
		len_h=ntohl(len);
		//printf("len_h:%d",len_h);
		if(res < 0){
			printf("1[srv] read len return %d and errno is %d\n", res, errno);
		}
		if(res == 0){
			printf("2[srv] read data return 0.\n");//注意！测试完将这个注释掉！
		}

		//read_amnt是已经读了多少，len_h是总共需要读多少，len_to_read是本次需要读多少，res是本次读了多少
		int read_amnt=0,len_to_read=len_h; 
		sign=0;
		do{
        res=read(sockfd, buf, len_to_read);
		read_amnt+=res;
		if(sign==0)
		{
			printf("[echo_rep] ");
		}
		if(read_amnt==len_h)
		{
			//经过多次读，读完了！可以开始printf了
			printf("%s",buf);
			sign=1;
			break;	
		}
		else if(read_amnt<len_h)
			
		{

			//没读完，需要再次读
			printf("%s",buf);
			len_to_read-=res;
			sign=2;
		}
		else{
			return 0;
		}

		}while(1);


		if(sign==1)
		{
			printf("\n");
		}
			
			

		
    }
	return 0;
}

int main(int argc, char* argv[])
{
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;
	int cli_addr_len;
	int connfd;
	if(argc != 3){
		printf("Usage:%s <IP> <PORT>\n", argv[0]);
		return 0;
	}

	struct sigaction sigact_pipe, old_sigact_pipe;
	sigact_pipe.sa_handler = sig_pipe;//sig_pipe()，信号处理函数
	sigemptyset(&sigact_pipe.sa_mask);
	sigact_pipe.sa_flags = 0;
	sigact_pipe.sa_flags |= SA_RESTART;//设置受影响的慢系统调用重启
	sigaction(SIGPIPE, &sigact_pipe, &old_sigact_pipe);

	//creat client fd
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&srv_addr, 0, sizeof(srv_addr));
	
	//初始化srv_addr_in
	srv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &srv_addr.sin_addr);
	srv_addr.sin_port = htons(atoi(argv[2]));
	
	//connect client to server
	do{
		int conn_res = connect(connfd, (struct sockaddr*) &srv_addr, sizeof(srv_addr));
		if(conn_res == 0){
			char ip_str[20]={0};
			printf("[cli] server[%s:%d] is connected!\n",inet_ntop(AF_INET, &srv_addr.sin_addr, ip_str, sizeof(ip_str)), ntohs(srv_addr.sin_port));
			if(!echo_rqt(connfd))
				break;
		}
		else if(conn_res == -1 && errno == EINTR){
			printf("[cli] connect error! errno is %d\n",errno);
			continue;		
		}
	}while(1);
	close(connfd);
	printf("[cli] connfd is closed!\n");
	printf("[cli] client is going to exit!\n");
	return 0;
}