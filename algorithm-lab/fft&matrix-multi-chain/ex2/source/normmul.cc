#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "lzq.h"

using std::vector;

void GetData(int poly_len, vector<double>& a, vector<double>& b){
    std::ifstream input_file("../input/input.txt");
    if(!input_file.is_open()){
        std::cerr << "Can't open input/input.txt file." << std::endl;
        exit(-1);
    }
    a.clear(); b.clear();
    double data_tmp;
    // get A(x) coe
    for(int pos = 0; pos < poly_len; ++pos){
        input_file >> data_tmp;
        a.push_back(data_tmp);
    }
    // get B(x) coe
    for(int pos = 0; pos < poly_len; ++pos){
        input_file >> data_tmp;
        b.push_back(data_tmp);
    }
}

void PrintIV(const vector<double>& a){
    for(auto e : a)
        std::cout << e << ' ';
    std::cout << std::endl;
}

vector<double> PolyMulti(const vector<double>& a, const vector<double>& b){
    int result_len = a.size() + b.size() - 1;
    vector<double> res(result_len, 0);
    for(int i = 0; i < a.size(); ++i){
        for(int j = 0; j < b.size(); ++j){
            res[i + j] += a[i] * b[j]; 
        }
    }
    return res;
}

int main(){
    const int datalen[4] = {4, 16, 32, 60};
    lzq::Timer timer;
    double time_count;
    std::ofstream time_file("../output/norm_time.txt");
    std::ofstream res_file("../output/norm_result.txt");
    if(!time_file.is_open() || !res_file.is_open()){
        std::cerr << "output file create failed." << std::endl;
        exit(-2);
    }

    vector<double> a, b;
    for(int i = 0; i < 4; ++i){
        GetData(datalen[i], a, b);
        timer.StartCount(); 
        vector<double> res = PolyMulti(a, b);
        timer.StopCount();
        timer.GetTimeSpan(time_count);
        // write result and time consuming into files
        res_file << "data len: " << datalen[i] << std::endl; 
        for(auto e : res){
            res_file << e << ' ';
        }
        res_file << std::endl;
        time_file << "data len: " << datalen[i] << ": " 
                   << time_count * 1E+6 << " us" << std::endl;
    }
    time_file.close(); res_file.close();
    return 0;
}

