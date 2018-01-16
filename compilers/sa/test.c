#include<stdio.h>
int main(){
    int i = 1;
    int j = 2;
    for(i = 1; i < 5; ++i){
        if(i > 3)
            ++j;
        else
            --j;
    }
    return 0;
}