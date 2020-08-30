#include<stdio.h>

union test{
    short value;
    char testEndian[2];
};


int main(){
    union test example;
    example.value=0x0102;
    if(example.testEndian[0]==0x02){
        printf("big endian\n");
    }else{
        printf("small endian\n");
    }
    return 0;
}