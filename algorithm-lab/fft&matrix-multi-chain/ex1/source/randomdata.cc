#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lzq.h"

using namespace std;

const int datalen[4] = {6, 11, 21, 31};

int main(){
    srand(time(NULL));
    // generatie random integer range
    string filename = string("../input/input") + string(".txt");
    ofstream inputfile(filename);
    if(!inputfile.is_open()){
        cerr << "can't create input file." << endl;
        return -1;
    }
    for(int i = 0; i < 32; ++i)
        inputfile << lzq::RandomInt(1, 300) << endl;
    inputfile.close();
    return 0;
}