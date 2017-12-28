#include <iostream>
#include "lzq.h"
#include <fstream>

int main(){
    std::vector<int> data;
    for(int count = 0; count < 60; ++count){
        data.push_back(count+1);
    }
    lzq::Random* ptr = lzq::Random::get();
    ptr->VecShuffle<int>(data);
    
    std::ofstream inputfile("../input/input.txt");
    for(auto e : data)
        inputfile << e << std::endl;
    inputfile << std::endl;
    inputfile.close();
    return 0;
}