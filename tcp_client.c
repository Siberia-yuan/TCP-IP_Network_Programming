#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void error_handling(char *args);

int main(int argc,char *argv[]){
    char message[30];
    int str_len=0;
    int idx=0;
    int read_len=0;


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

    sock=socket(PF_INET,SOCK_STREAM,NULL);
    if(sock==-1){
        error_handling("socket() error");
    }

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("connect error");
    }

    while(read_len=read(sock,&message[idx++],1)){
        if(read_len==-1)
            error_handling("rea() error");
        str_len+=read_len;
    }
    printf("message form server: %s\n",message);
    printf("read call count: %d\n",str_len);
    close(sock);
    return 0;
}


void error_handling(char *args){
    fputs(args,stderr);
    fputc('\n',stderr);
    exit(1);
}
