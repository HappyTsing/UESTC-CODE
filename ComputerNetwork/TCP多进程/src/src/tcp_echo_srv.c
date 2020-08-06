#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <assert.h>

#define BACKLOG 1024
#define printftoflie(fp, format, ...)            \
	if(fp == NULL){printf(format, ##__VA_ARGS__);} 	\
	else{printf(format, ##__VA_ARGS__);	\
			fprintf(fp, format, ##__VA_ARGS__);fflush(fp);}

int sig_type = 0, sig_to_exit = 0;
FILE *fp_res = NULL; 

void sig_int(int signo)
{
    sig_type = signo;
    sig_to_exit = 1;
    printftoflie(fp_res, "[srv](%d) SIGINT is coming!\n", getpid());
}
void sig_pipe(int signo)
{
    sig_type = signo;
    sig_to_exit = 1;
    printftoflie(fp_res, "[srv](%d) SIGPIPE is coming!\n", getpid());
}
void sig_chld(int signo)
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printftoflie(fp_res, "[srv](%d) SIGCHLD is coming!\n", getpid());
    }
    sig_type = signo;
    sig_to_exit = 1;
}

int install_sig_handlers()
{
    int res = -1;
    struct sigaction sigact_pipe, old_sigact_pipe;
    sigact_pipe.sa_handler = &sig_pipe; 
    sigact_pipe.sa_flags = 0;
    sigact_pipe.sa_flags |= SA_RESTART;
    sigemptyset(&sigact_pipe.sa_mask);
    res = sigaction(SIGPIPE, &sigact_pipe, &old_sigact_pipe);
    if (res)
        return -1;
    struct sigaction sigact_chld, old_sigact_chld;
    sigact_chld.sa_handler = &sig_chld;
    sigemptyset(&sigact_chld.sa_mask);
    sigact_chld.sa_flags = 0;
    sigact_chld.sa_flags |= SA_RESTART;
    res = sigaction(SIGCHLD, &sigact_chld, &old_sigact_chld);
    if (res)
    {
        return -2;
    struct sigaction sigact_int, old_sigact_int;
    sigact_int.sa_handler = &sig_int;
    sigemptyset(&sigact_int.sa_mask);
    sigact_int.sa_flags = 0;
    res = sigaction(SIGINT, &sigact_int, &old_sigact_int);
    if (res)
    {
        return -3;
    }
    return 0;
}
int judgeres(int sig,int res,pid_t pid,int pin_h,int len_h)
{
	if(sig==0){
		
        if (res < 0)
        {
            printftoflie(fp_res, "[srv](%d) read pin_n return %d and errno is %d!\n", pid, res, errno);
            if (errno == EINTR)
            {
                if (sig_type == SIGINT)
                    return pin_h;
            }
            return pin_h;
        }
        else if (res == 0)
        {
            return pin_h;
        
	}
	else if(sig==1)
	{
        if (res < 0)
        {
            printftoflie(fp_res, "[srv](%d) read len_n return %d and errno is %d\n", pid, res, errno);
            if (errno == EINTR)
            {
                if (sig_type == SIGINT)
                    return len_h;
            }
            return len_h;
        }
        else if (res == 0)
        {
            return len_h;
       
	}
	else
	{
		return 0;
	}
}

int echo_rep(int sockfd)
{
    int len_h = -1, len_n = -1; 
    int pin_h = -1, pin_n = -1;
    int res = 0;
    char *buf = NULL;
    pid_t pid = getpid();
	int sig;

    do
    {
        res = read(sockfd, &pin_n, sizeof(pin_n));
		sig=0;
		judgeres(sig,res,pid,pin_h,len_h);
        pin_h = ntohl(pin_n);
        res = read(sockfd, &len_n, sizeof(len_n));
		sig=1;
		judgeres(sig,res,pid,pin_h,len_h);
        len_h = ntohl(len_n);
        buf = (char *)malloc(len_h * sizeof(char) + 8); 
        int read_amnt = 0, len_to_read = len_h;
        do
        {
            res = read(sockfd, buf + read_amnt + 8, len_to_read);
            if (res < 0)
            {
                printftoflie(fp_res, "[srv](%d) read data return %d and errno is %d,\n", pid, res, errno);
                if (errno == EINTR)
                {
                    if (sig_type == SIGINT)
                    {
                        free(buf);
                        return pin_h;
                    }
                    continue;
                }
                free(buf);
                return pin_h;
            }
            else if (res == 0)
            {
                free(buf);
                return pin_h;
            }
            read_amnt = read_amnt + res;
            if (read_amnt == len_h)
            {
                break;
            }
            else if (read_amnt < len_h)
            {
                len_to_read = len_h - read_amnt;
                continue;
            }
            else
            {
                free(buf);
                return pin_h;
            }

        } while (1);
        printftoflie(fp_res, "[echo_rqt](%d) %s\n", pid, buf + 8);
        memcpy(buf, &pin_n, 4);
        memcpy(buf + 4, &len_n, 4);
        res = write(sockfd, buf, len_h + 8);
        free(buf);
    } while (1);
    return pin_h;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage:%s <IP> <PORT>\n", argv[0]);
        return -1;
    }
    pid_t pid = getpid();
    char ip_str[20] = {0}; 
    char fn_res[20] = {0}; //
    int res = -1;
    res = install_sig_handlers();
    if (res != 0)
    {
        printf("[srv](%d) filed to install signal handlers!\n", pid);
    }
    fp_res = fopen("stu_srv_res_p.txt", "wb");
    if (!fp_res)
    {
        printf("[srv](%d) failed to open file \"stu_srv_res_p.txt\"!\n", pid);
        return res;
    }
    else
    {
        printf("[srv](%d) stu_srv_res_p.txt is opend!\n", pid);
    }
    struct sockaddr_in srv_addr;
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_len;
    int listenfd, connfd;
    bzero(&srv_addr, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &srv_addr.sin_addr);
    srv_addr.sin_port = htons(atoi(argv[2]));
    printftoflie(fp_res, "[srv](%d) server[%s:%d] is initializing!\n",
            pid, inet_ntop(AF_INET, &srv_addr.sin_addr, ip_str, sizeof(ip_str)), (int)ntohs(srv_addr.sin_port));
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    listen(listenfd, BACKLOG);
    while (!sig_to_exit)
    {
        cli_addr_len = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
        if (connfd == -1 && errno == EINTR)
        {
            if (sig_type == SIGINT)
                break;
            continue;
        }
        printftoflie(fp_res, "[srv](%d) client[%s:%d] is accepted!\n", pid, inet_ntop(AF_INET, &cli_addr.sin_addr, ip_str, sizeof(ip_str)), (int)ntohs(cli_addr.sin_port));

        if (!fork())
        { 
            pid = getpid();
            sprintf(fn_res, "stu_srv_res_%d.txt", pid);
            fp_res = fopen(fn_res, "wb"); 
            if (!fp_res)
            {
                printf("[srv](%d) child exits, failed to open file \"stu_srv_res_%d.txt\"!\n", pid, pid);
                exit(-1);
            }
            printf("[srv](%d) stu_srv_res_%d.txt is opend!\n", pid, pid);
            printftoflie(fp_res, "[srv](%d) child process is created!\n", pid);
            close(listenfd);
            printftoflie(fp_res, "[srv](%d) listenfd is closed!\n", pid);
            int pin = echo_rep(connfd);
            if (pin < 0)
            {
                printftoflie(fp_res, "[srv](%d) child exits, client PIN returned by echo_rqt() error!\n", pid);
                exit(-1);
            }

            char fn_res_n[20] = {0};
            sprintf(fn_res_n, "stu_srv_res_%d.txt", pin);
            if (!rename(fn_res, fn_res_n))
            {
                printftoflie(fp_res, "[srv](%d) res file rename done!\n", pid);
            }
            else
            {
                printftoflie(fp_res, "[srv](%d) child exits, res file rename failed!\n", pid);
            }
            close(connfd);
            printftoflie(fp_res, "[srv](%d) connfd is closed!\n", pid);
            printftoflie(fp_res, "[srv](%d) child process is going to exit!\n", pid);
            fclose(fp_res);
            printf("[srv](%d) stu_cli_res_%d.txt is closed!\n", pid, pid);
            exit(1);
        }
        else
        { 
            close(connfd);
        }
    }
	
    close(listenfd);
    printftoflie(fp_res, "[srv](%d) listenfd is closed!\n", pid);
    printftoflie(fp_res, "[srv](%d) parent process is going to exit!\n", pid);
    fclose(fp_res);
    printf("[srv](%d) stu_cli_res_p.txt is closed!\n", pid);
    return 0;
}

