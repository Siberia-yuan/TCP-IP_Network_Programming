#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_routine(int sock,char *buf);
void write_routine(int sock,char *buf);

int main(int argc,char* argv[]){
    int sock;
    pid_t pid;
    struct sockaddr_in dstAddr;
    char buf[BUF_SIZE];

    memset(&dstAddr,0,sizeof(dstAddr));
    dstAddr.sin_addr.s_addr=inet_addr(argv[1]);
    dstAddr.sin_family=AF_INET;
    dstAddr.sin_port=htons(atoi(argv[2]));

    if(argc!=3){
        printf("Usage:%s <ip> <port>\n",argv[0]);
        exit(1);
    }

    sock=socket(PF_INET,SOCK_STREAM,0);

    // if(bind(sock,(struct sockaddr*)&dstAddr,sizeof(dstAddr))==-1){
    //     error_handling("bind() error");
    // }

    if(connect(sock,(struct sockaddr*)&dstAddr,sizeof(dstAddr))==-1){
        error_handling("connect() error");
    }

    pid=fork();
    if(pid==0){
        read_routine(sock,buf);
    }else{
        write_routine(sock,buf);
    }

    close(sock);
    return 0;
}

void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

void read_routine(int sock,char *buf){
    while(1){
        int str_len=read(sock,buf,BUF_SIZE);
        if(str_len==0){
            return;
        }
        printf("message from server:\n%s\n",buf);
    }
}
void write_routine(int sock,char *buf){
    while(1){
        fgets(buf,BUF_SIZE,stdin);
        if(!strcmp("q\n",buf)||!strcmp("Q\n",buf)){
            shutdown(sock,SHUT_WR);
            return;
        }
        write(sock,buf,strlen(buf));
    }
}