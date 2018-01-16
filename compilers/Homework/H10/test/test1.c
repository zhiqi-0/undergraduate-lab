#include <stdio.h>
int main(){
    int a = 2;
    unsigned b = 2;
    int count = 0;
    printf("start counting...\n");
    while(a + b >= 0){
        count = count + 1;
        a = a - 1;
    }
    printf("count result: %d\n", count);
    return 0;
}