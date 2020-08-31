#include<stdio.h>
#include<unistd.h>
int gval=10;
int main(int argc,char *argv[]){
    pid_t pid;
    int lval=10;
    gval++,lval+=5;
    pid=fork();
    if(pid==0){
        printf("In child process\n");
        gval+=2,lval+=2;
    }else{
        printf("In parent process\n");
        gval-=2,lval-=2;
    }

    if(pid==0){
        printf("In child process\n");
        printf("gval:%d lval:%d\n",gval,lval);
    }else{
        printf("In parent process\n");
        printf("gval:%d lval:%d\n",gval,lval);
    }
    return 0;
}