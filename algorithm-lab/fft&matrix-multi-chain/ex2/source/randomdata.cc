#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lzq.h"

using namespace std;

const int datalen = 120;

int main(){
    srand(time(NULL));
    // generatie random integer range
    string filename = string("../input/input") + string(".txt");
    ofstream inputfile(filename);
    if(!inputfile.is_open()){
        cerr << "can't create input file." << endl;
        return -1;
    }
    for(int i = 0; i < datalen; ++i)
        inputfile << lzq::RandomFloat(0, 1000) << endl;
    inputfile.close();
    return 0;
}