#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

#define MAX_THREAD 5
void* threadRun(void* args);


int main(){
    pthread_t tids[MAX_THREAD];
    for(int i=0;i<MAX_THREAD;i++){
        pthread_create(&tids[i],NULL,threadRun,NULL);
        pthread_join(tids[i],NULL);
    }
    return 0;
}

void* threadRun(void* args){
    cout<<"Execute threadRun"<<endl;
    sleep(2);
}