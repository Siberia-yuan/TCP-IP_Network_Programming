#include<stdio.h>
#include<unistd.h>

int main(int argc,char* argv[]){
    pid_t pid=fork();
    if(pid==0){
        printf("child process\n");
    }else{
        printf("Parent process");
        sleep(10);
    }

    if(pid==0){
        printf("end child process\n");
    }else{
        printf("end parent process");
    }
    return 0;
}