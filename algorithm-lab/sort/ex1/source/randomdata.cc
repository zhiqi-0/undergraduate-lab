#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lzq.h"

using namespace std;

string RandomString(int len){
    int strsize = rand()%(32) + 1;
    string str;
    str.resize(strsize);
    for(int i = 0; i < strsize; ++i)
        str[i] = (char)lzq::RandomInt('a','z');
    return str;
}

int main(){
    srand(time(NULL));
    // generate random string array
    ofstream randomstr("randomstr.data");
    ofstream randomint("randomint.data");
    for(int i = 0; i < (1 << 17); ++i){
        randomstr << RandomString(32) << endl;
        randomint << lzq::RandomInt(1, 65535) << endl;
    }
    randomstr.close(); randomint.close();
    return 0;
}