#include<iostream>
#include<pthread.h>

using namespace std;

#define MAX 5
void* thread_run(void* args);
typedef struct sample{
    int i;
    int j;
}sasa;

void* thread_run(void* args){
    sasa* stru=(sasa *)args;
    cout<<stru->i<<stru->j<<endl;
    pthread_exit(NULL);
}

int main(){
    pthread_t pid[MAX];
    sasa* str[MAX];
    for(int k=0;k<MAX;k++){
        str[k]=new sasa;
        str[k]->i=k+1;
        str[k]->j=(k+1)*(k+1);
    }
    for(int k_1=0;k_1<MAX;k_1++){
        pthread_create(&pid[k_1],NULL,thread_run,(void *)str[k_1]);
    }
    pthread_exit(NULL);
    return 0;
}

