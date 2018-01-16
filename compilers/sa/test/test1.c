#include<stdio.h>

int main(){
    FILE *pf1, *pf2;
    pf1 = fopen("test1.txt", "r");
    pf1 = fopen("test2.txt", "r");
    //fclose(pf1);
    fclose(pf1);
    return 0;
}