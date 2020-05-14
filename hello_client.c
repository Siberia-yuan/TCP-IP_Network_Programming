#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void error_handling(char *message);
int main(int argc, char *argv[]){
    int sock;
    


}







void error_handling(char *message){\
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}