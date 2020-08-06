
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>

#define BACKLOG 1024

int sig_type = 0;
int sig_to_exit = 0;

void sig_int(int signo) {	
	sig_type = signo;
	printf("[srv] SIGINT is coming!\n");
	printf("[srv] accept return -1 and errno is EINTR\n");
    sig_to_exit = 1;
}

void sig_pipe(int signo) {	
	sig_type = signo;
	printf("[srv] SIGPIPE is coming!\n");
}

void echo_rep(int sockfd)
{
	int len = 0;
	int res =0,res_used_to_write=0;
	char *buf = NULL;
	char *buf_used_to_write=NULL;
	int len_h=0;  //主机字节序
	int len_n=0;  //网络字节序
	int sign=0;  //三个取值：0 1 2，0表示初次读取，输出[echo_rep] ，1表示读取完毕，输出换行符，2表示循环读取，不输出换行符。
	int sign_buf=0;
	int i;
	// Read sockfd and write back
    do {
		res = read(sockfd, &len, sizeof(int));
		len_h=ntohl(len);
		if(res < 0){
			printf("[srv] read len return %d and errno is %d\n", res, errno);
			if(errno == EINTR){
				printf("Test 1\n");
				if(sig_type == SIGINT){
					printf("Test 2\n");
					return;	
				}
				continue;
			}
			return;
		}
		if(res == 0){
			//printf("[srv] read data return 0.\n");//注意！测试完将这个注释掉！
			return;
		}
		//read_amnt是已经读了多少，len_h是总共需要读多少，len_to_read是本次需要读多少，res是本次读了多少!!
		int read_amnt = 0, len_to_read = len_h;
		buf = (char*)malloc(len_h * sizeof(char));
		buf_used_to_write=(char*)malloc(len_h * sizeof(char));
		memset(buf, 0, sizeof(*buf));
		memset(buf_used_to_write, 0, sizeof(*buf_used_to_write));
		sign=0;
		sign_buf=0;
		res_used_to_write=0;
		do{
			//printf("[srv] len to read is %d\n", len_to_read);
			res = read(sockfd, buf, len_to_read);
		
			if(sign_buf==0)
				{
					for(i=0;i<res;i++)
					{
						buf_used_to_write[res_used_to_write+i]=buf[i];
					}
					res_used_to_write=res;
					sign_buf=1;
				}
			if(res < 0){
				printf("[srv] read data return %d and errno is %d\n", res, errno);
				if(errno == EINTR){
					printf("Test 3\n");	
					if(sig_type == SIGINT){
						printf("Test 4\n");
						free(buf);
						free(buf_used_to_write);
						return;
					}
					continue;
				}
				free(buf);
				return;
			}
			if(res == 0){
				//printf("[srv] read data return 0.\n");//注意！测试完将这个注释掉！
				free(buf);
				free(buf_used_to_write);
				return;
			}

			read_amnt += res;
			if(sign==0){
				printf("[echo_rqt] ");
			}
			if(read_amnt == len_h){
				//printf("[srv] read done as expected wtih read_amnt[%d]\n", read_amnt);//注意！测试完将这个注释掉！
				printf("%s",buf);
				sign=1;
				if(sign_buf==2)
				{
					for(i=0;i<res;i++)
					{
						buf_used_to_write[res_used_to_write+i]=buf[i];
					}
				}
				break;
			}
			else if(read_amnt < len_h){
				//printf("[srv] read_amnt < len\n");
				printf("%s",buf);
				sign=2;
				len_to_read -= res;
				sign_buf=2;  //确定是否需要在read_amnt==len_h的判定中赋值。
				for(i=0;i<res;i++)
				{
					buf_used_to_write[res_used_to_write+i]=buf[i];
				}
				res_used_to_write+=res;
			}
			else{
				//printf("[srv] read_amnt > len\n");
				free(buf);
				free(buf_used_to_write);
				return;
			}
			
		}while(1);

		if(sign==1)
		{
			printf("\n");
		}
			
		len_n=htonl(len_h);
        write(sockfd, &len_n, sizeof(len_n));
        write(sockfd, buf_used_to_write, len_h);
		//printf("[srv] write() done as expected wtih read_amnt[%d]\n", read_amnt);		
        free(buf);
		free(buf_used_to_write);
    }while(1);
}

int main(int argc, char* argv[])
{
	//error check
	if(argc != 3)
	{
		printf("Usage: tcp_echo_srv <addr> <port>\n");
		return 0;
	}

	struct sigaction sigact_pipe, old_sigact_pipe;
	sigact_pipe.sa_handler = sig_pipe;//sig_pipe()，信号处理函数
	
	sigemptyset(&sigact_pipe.sa_mask);
	
	sigact_pipe.sa_flags = 0;
	sigact_pipe.sa_flags |= SA_RESTART;//设置受影响的慢系统调用重启
	sigaction(SIGPIPE, &sigact_pipe, &old_sigact_pipe);

//安装SIGINT信号处理器
	struct sigaction sigact_int, old_sigact_int;
    sigact_int.sa_handler = &sig_int;
    sigemptyset(&sigact_int.sa_mask);
    sigact_int.sa_flags = 0;
	
    sigaction(SIGINT, &sigact_int, &old_sigact_int);

	char ip_str[20]={0};//用于IP地址转换
	//定义服务器、客户端Socket地址
	struct sockaddr_in srv_addr ,cli_addr;
	
	int listenfd, connfd;
	socklen_t clilen;


	bzero(&srv_addr, sizeof(srv_addr));

    //srv_addr三个数据初始化
	srv_addr.sin_family = AF_INET;
	//srv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	inet_pton(AF_INET,argv[1],&srv_addr.sin_addr);
	srv_addr.sin_port = htons(atoi(argv[2]));
	
	
	printf("[srv] server[%s:%d] is initializing!\n", inet_ntop(AF_INET, &srv_addr.sin_addr, ip_str, sizeof(ip_str)), (int)ntohs(srv_addr.sin_port));
    

	listenfd = socket(AF_INET, SOCK_STREAM, 0);	
	bind(listenfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
	listen(listenfd,BACKLOG);

	while(!sig_to_exit)
	{
		clilen = sizeof(cli_addr);
		connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);
		if(connfd == -1 && errno == EINTR)
		{
			break;
		}
		

        if (connfd < 0) continue;
		
		printf("[srv] client[%s:%d] is accepted!\n", inet_ntop(AF_INET, &cli_addr.sin_addr, ip_str, sizeof(ip_str)), (int)ntohs(cli_addr.sin_port));
		echo_rep(connfd);
		close(connfd);
		printf("[srv] connfd is closed!\n");
	}
	close(listenfd);
	printf("[srv] listenfd is closed!\n");
	printf("[srv] server is going to exit\n");
	return 0;
}