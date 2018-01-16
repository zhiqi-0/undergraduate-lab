#include<stdio.h>
void test(int *p){
    int c = *p;
    if(p == 0)
        return;
    printf("Now Here\n");
    *p = 2333;
}

int main(){
    int* p = NULL;
    printf("ok\n");
    test(p);
    return 0;
}