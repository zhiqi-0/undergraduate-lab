#include<iostream>
#include <vector>

void print(std::vector<int> v){
    for(auto e : v)
        std::cout << e << ' ';
    std::cout << std::endl;
}
int main(){
    int p[3] = {1,2,3};
    print(std::vector<int>(&p[0], &p[3]));
    return 0;
}