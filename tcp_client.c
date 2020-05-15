#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void error_handling(char *args);

int main(int argc,char *argv[]){
    if(argc!=3){
        printf("Usage:%s <ip> <port>",argv[0]);
        exit(1);
    }

    int sock;
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

}


void error_handling(char *args){
    fputs(args,stderr);
    fputc('\n',stderr);
    exit(1);
}
