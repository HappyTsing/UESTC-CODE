/*
	TCP ECHO单进程客户端
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
#define MAX_CMD_STR 100

void sig_pipe(int signo) {	
	printf("[cli] SIGPIPE is coming!\n");
}

int echo(int sockfd)
{
    char buf[MAX_CMD_STR+1];
    while (fgets(buf, MAX_CMD_STR, stdin)) {
		if(strncmp(buf, "exit", 4) == 0){
			break;
		}

		int len = strnlen(buf, MAX_CMD_STR);
		if(buf[len-1] == '\n')	// If only '\n' input, '\0' will be send out;
			buf[len-1] = 0;

        write(sockfd, &len, sizeof(len));
        write(sockfd, buf, len);
        memset(buf, 0, sizeof(buf));
        read(sockfd, &len, sizeof(len));
        read(sockfd, buf, len);
        printf("[echo_rep] %s\n", buf);
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
	connfd = socket(PF_INET, SOCK_STREAM, 0);
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &srv_addr.sin_addr);
	srv_addr.sin_port = htons(atoi(argv[2]));
	//connect client to server
	do{
		int conn_res = connect(connfd, (struct sockaddr*) &srv_addr, sizeof(srv_addr));
		if(conn_res == 0){
			char ip_str[20]={0};
			printf("[cli] server[%s:%d] is connected!\n",inet_ntop(AF_INET, &srv_addr.sin_addr, ip_str, sizeof(ip_str)), ntohs(srv_addr.sin_port));
			if(!echo(connfd))
				break;
		}
		else if(conn_res == -1 && errno == EINTR){
			continue;		
		}
	}while(1);
	close(connfd);
	printf("[cli] connfd is closed!\n");
	printf("[cli] client is exiting!\n");
	return 0;
}