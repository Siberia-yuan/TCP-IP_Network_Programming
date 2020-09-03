/**
 * 套接字资源为操作系统独自占有
 * 即便fork了一个进程多个文件描述符指向同一个套接字
 * 
 * io分割：拆分成多个进程，一个进程负责接受数据，另一个进程负责发送数据
 * 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);
void read_childproc(int sig);
void handling_int(int sig);
void handing_child(int sig);

int main(int argc,char* argv[]){

    if(argc!=2){
        printf("Usage:%s <port>",argv[0]);
        exit(1);
    }

    //inital variables
    pid_t pid;
    int server_sock,clnt_sock;
    struct sockaddr_in serverAddr,clntAddr;
    char buf[BUF_SIZE];
    socklen_t clnt_len=sizeof(clntAddr);

    //initiallization of server address
    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddr.sin_port=htons(atoi(argv[1]));
    serverAddr.sin_family=AF_INET;

    //signal registeration
    signal(SIGINT,handling_int);
    signal(SIGCHLD,handing_child);

    //initiallization of server socket
    server_sock=socket(PF_INET,SOCK_STREAM,0);

    if(bind(server_sock,(const struct sockaddr*)&serverAddr,sizeof(serverAddr))==-1){
        error_handling("bind() error");
    }

    if(listen(server_sock,5)==-1){
        error_handling("listen() error");
    }

    while(1){
        clnt_sock=accept(server_sock,(struct sockaddr*)&clntAddr,&clnt_len);
        if(clnt_sock==-1){
            continue;
        }else{
            puts("connecting to a new client...\n");
            pid=fork();
            if(pid==-1){
                close(clnt_sock);
                continue;
            }
            if(pid==0){
                //subpprocess handling the request from the client
                int str_len;
                while((str_len=read(clnt_sock,buf,BUF_SIZE))!=0){
                    write(clnt_sock,buf,str_len);
                }
                close(clnt_sock);
                puts("terminating connection...\n");
                return 0;
            }
            close(clnt_sock);
        }
    }
    close(server_sock);
    return 0;
}


void handling_int(int sig){
    if(sig==SIGINT){
        printf("Ctrl+C pressed\nExiting...\n");
        exit(1);
    }
    return;
}


void handing_child(int sig){
    int status;
    int pid;
    if(sig==SIGCHLD){
        pid=waitpid(-1,&status,WNOHANG);
        printf("child process removed with pid:%d\n",pid);
    }
    return;
}

void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}