#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
    int status;
    pid_t pid=fork();
    if(pid==0){
        sleep(5);
        return 24;
    }else{
        while(!waitpid(-1,&status,WNOHANG)){
            sleep(1);
            fputs("waiting...\n",stdout);
        }
        if(WIFEXITED(status)){
            printf("child send %d \n",WEXITSTATUS(status));
        }
    }
    return 0;
}