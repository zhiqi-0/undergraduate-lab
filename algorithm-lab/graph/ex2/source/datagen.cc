#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "lzq.h"

void datagen(std::size_t vertex_num, std::string filename){
    std::ofstream inputfile(filename);
    if(!inputfile.is_open()){
        std::cout << "error opening input file.\n";
        exit(1);
    }
    int k = 0, res = 1;
    while(res < vertex_num){
        k += 1;
        res = res << 1;
    }
    int edge_num = vertex_num * k;
    auto random = lzq::Random::get();
    for(int i = 0; i < edge_num; ++i){
        int vertex1 = random->RandomInt(0, vertex_num - 1);
        inputfile << vertex1 << ',';
        inputfile << random->RandomInt(1, vertex_num) << ',';
        int vertex2;
        do{
            vertex2 = random->RandomInt(0, vertex_num - 1);
        }while(vertex2 == vertex1);
        inputfile << vertex2 << std::endl;
    }
    inputfile.close();
}

int main(){
    const int vertexsize[6] = {8, 16, 32, 64, 128, 256};
    for(int i = 0; i < 6; ++i){
        std::string filename = std::string("../input/size") + std::to_string(i + 1) + std::string("/input.txt");
        datagen(vertexsize[i], filename);
    }
    return 0;
}

