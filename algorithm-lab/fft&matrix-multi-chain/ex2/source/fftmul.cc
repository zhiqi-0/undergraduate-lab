#include <iostream>
#include <fstream>
#include <cstdlib>
#include <complex>
#include <vector>
#include <cmath>
#include "lzq.h"

using std::vector;
using std::complex;
using std::polar;
typedef vector<complex<double> > CVector;
int count;

// get data from ../input/input.txt. Note that poly_len should be less equal than 60
void GetData(int poly_len, CVector& a, CVector& b){
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
        a.push_back(complex<double>((double)data_tmp, 0));
    }
    // get B(x) coe
    for(int pos = 0; pos < poly_len; ++pos){
        input_file >> data_tmp;
        b.push_back(complex<double>((double)data_tmp, 0));
    }
    // make up to 2^k
    int s = 1;
    while(s < poly_len){
        s = s << 1;
    }
    int add_0 = s - poly_len;
    for(int i = 0; i < add_0; ++i){
        a.push_back(complex<double>(0, 0));
        b.push_back(complex<double>(0, 0));
    }
}

// for debug
void PrintCV(const CVector& a){
    for(auto e : a)
        std::cout << e << ' ';
    std::cout << std::endl;
}

CVector RecursiveFft(const CVector& a, bool forward = true){
    //std::cout << count++ << std::endl;
    int n = a.size();
    //std::cout << n << std::endl;
    if(n == 1){
        complex<double> res = a[0];
        return CVector(1, res);
    }
    int ndiv2 = n >> 1;
    complex<double> wn;
    if(forward)
        wn = polar(1.0, 2 * M_PI / n);
    else
        wn = polar(1.0, -2 * M_PI / n);
    //std::cout << wn << std::endl;
    complex<double> w = 1;
    CVector a0(ndiv2);
    CVector a1(ndiv2);
    for(int i = 0; i < ndiv2; ++i){
        a0[i] = a[i << 1];
        a1[i] = a[(i << 1) + 1];
    }
    CVector y0 = RecursiveFft(a0, forward);
    CVector y1 = RecursiveFft(a1, forward);
    CVector res(n);
    for(int k = 0; k < ndiv2; ++k){
        res[k] = y0[k] + w * y1[k];
        res[k + ndiv2] = y0[k] - w * y1[k];
        w = w * wn;
    }
    return res;
}

vector<double> MultiPoly(CVector a, CVector b, int poly){
    // expansion array size double times
    int len = a.size();
    CVector expansion(len, complex<double>(0, 0));
    a.insert(a.end(), expansion.begin(), expansion.end());
    b.insert(b.end(), expansion.begin(), expansion.end());
    // Forward FFT
    CVector ya = RecursiveFft(a);
    CVector yb = RecursiveFft(b);
    CVector yc(len << 1);
    // Multiply
    for(int i = 0; i < (len << 1); ++i)
        yc[i] = ya[i] * yb[i];
    // Backward FFT
    CVector cc = RecursiveFft(yc, false);
    // Get result
    int res_len = (poly << 1) - 1;
    vector<double> c(res_len);
    for(int i = 0; i < res_len; ++i){
        c[i] = cc[i].real() / (len << 1);
    }
    return c;
}

int main(){
    const int datalen[4] = {4, 16, 32, 60};
    lzq::Timer timer;
    double time_count;
    std::ofstream time_file("../output/fft_time.txt");
    std::ofstream res_file("../output/fft_result.txt");
    if(!time_file.is_open() || !res_file.is_open()){
        std::cerr << "output file create failed." << std::endl;
        exit(-2);
    }

    CVector a, b;
    for(int i = 0; i < 4; ++i){
        GetData(datalen[i], a, b);
        timer.StartCount(); 
        vector<double> res = MultiPoly(a, b, datalen[i]);
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