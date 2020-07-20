/*
	TCP ECHO单进程循环服务器
	@2020 UESTC 信息与软件工程学院 《计算机网络系统》课程组
*/
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
    sig_to_exit = 1;
}

void sig_pipe(int signo) {	
	sig_type = signo;
	printf("[srv] SIGPIPE is coming!\n");
}

void echo_rep(int sockfd)
{
	int len = 0;
	int read_res;
	char *buf = NULL;

	// Read sockfd and write back
    do {
		read_res = read(sockfd, &len, sizeof(len));
		if(read_res < 0){
			printf("[srv] read len return %d and errno is %d\n", read_res, errno);
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
		if(read_res == 0){
			// printf("[srv] read data return 0.\n");
			return;
		}
		
		int read_amnt = 0, len_to_read = len;
		buf = (char*)malloc(len * sizeof(char));
		do{
			//printf("[srv] len to read is %d\n", len_to_read);
			read_res = read(sockfd, buf, len_to_read);
			if(read_res < 0){
				printf("[srv] read data return %d and errno is %d\n", read_res, errno);
				if(errno == EINTR){
					printf("Test 3\n");	
					if(sig_type == SIGINT){
						printf("Test 4\n");
						free(buf);
						return;
					}
					continue;
				}
				free(buf);
				return;
			}
			if(read_res == 0){
				// printf("[srv] read data return 0.\n");
				free(buf);
				return;
			}

			read_amnt += read_res;
			if(read_amnt == len){
				//printf("[srv] read done as expected wtih read_amnt[%d]\n", read_amnt);
				break;
			}
			else if(read_amnt < len){
				printf("[srv] read_amnt < len\n");
				len_to_read = len - read_amnt;
			}
			else{
				printf("[srv] read_amnt > len\n");
				free(buf);
				return;
			}
			
		}while(1);

		printf("[echo_rqt] %s\n", buf);
		write(sockfd, &len, sizeof(len));
        write(sockfd, buf, len);
		//printf("[srv] write() done as expected wtih read_amnt[%d]\n", read_amnt);		
        free(buf);
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

	struct sigaction sigact_int, old_sigact_int;
    sigact_int.sa_handler = &sig_int;
    sigemptyset(&sigact_int.sa_mask);
    sigact_int.sa_flags = 0;
    sigaction(SIGINT, &sigact_int, &old_sigact_int);

	char ip_str[20]={0};//用于IP地址转换
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr, cli_addr_peer;
	int listenfd, connfd, cli_addr_peer_len;
	socklen_t clilen;

	listenfd = socket(PF_INET, SOCK_STREAM, 0);	

	bzero(&srv_addr, sizeof(srv_addr));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	srv_addr.sin_port = htons(atoi(argv[2]));
	printf("[srv] server[%s:%d] is initializing!\n", inet_ntop(AF_INET, &srv_addr.sin_addr, ip_str, sizeof(ip_str)), (int)ntohs(srv_addr.sin_port));
    
	bind(listenfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
	listen(listenfd,BACKLOG);

	while(!sig_to_exit)
	{
		clilen = sizeof(cli_addr);
		connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);
		if(connfd == -1 && errno == EINTR)
			break;

		printf("[srv] client[%s:%d] is accepted!\n", inet_ntop(AF_INET, &cli_addr.sin_addr, ip_str, sizeof(ip_str)), (int)ntohs(cli_addr.sin_port));

        if (connfd < 0) continue;
		echo_rep(connfd);
		close(connfd);
		printf("[srv] connfd is closed!\n");
	}
	close(listenfd);
	printf("[srv] listenfd is closed!\n");
	printf("[srv] server is exiting\n");
	return 0;
}