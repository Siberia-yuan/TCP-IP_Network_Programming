#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
    int status;
    pid_t pid=fork();
    if(pid==0){
        sleep(2);
        return 3;
    }else{
        printf("child pid %d \n",pid);
        pid=fork();
        if(pid==0){
            sleep(2);
            exit(7);
        }else{
            printf("child PID: %d\n",pid);
            wait(&status);
            if(WIFEXITED(status)){
                printf("child send one:%d\n",WIFEXITED(status));
            }
            wait(&status);
            if(WIFEXITED(status)){
                printf("child send two:%d\n",WIFEXITED(status));
            }
            sleep(2);
            printf("terminates\n");
        }
    }
    return 0;
}