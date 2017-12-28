#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "lzq.h"
#include <climits>

using namespace std;

lzq::Timer timer;
ofstream result_file = ofstream("../output/result.txt");
ofstream time_file = ofstream("../output/time.txt");

void GetSourceData(int matrixnum, vector<int>& data){
    string filename = string("../input/input.txt");
    ifstream datafile = ifstream(filename);
    if(!datafile.is_open()){
        cerr << filename << ": file not exists" << endl;
        exit(-2);
    }
    data.clear();
    for(int i = 0; i < matrixnum + 1; ++i){
        int res;
        datafile >> res;
        data.push_back(res);
    }
}
/* \brief use dp to cal matrix multiply order
 * param: matrixnum: number of matrix multiply
 * param: data: data vector of matrix row, colomn number
 * return: time used for calculate orders
 */
double CalMatrixOrder(int matrixnum, vector<int>& data){
    void PrintParens(vector< vector<int> > s, int i, int j);
    // start counting time
    double time_count;
    timer.StartCount();
    // start using dp
    int n = matrixnum;
    vector< vector<int> > m(n + 1);
    vector< vector<int> > s(n + 1);
    for(int i = 0; i < n + 1; ++i){
        m[i].resize(n + 1);
        s[i].resize(n + 1);
        m[i][i] = s[i][i] = 0;
    }
    for(int l = 2; l <= n; ++l){
        for(int i = 1; i <= n - l + 1; ++i){
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for(int k = i; k <= j - 1; ++k){
                int q = m[i][k] + m[k + 1][j] + data[i - 1] * data[k] * data[j];
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    // endl using dp
    // end counting time
    timer.StopCount();
    timer.GetTimeSpan(time_count);
    time_file << "Matrix Num: " << matrixnum - 1 << " time: " << time_count * 1E+6 << "us" << endl;
    // write & print order result
    PrintParens(s, 1, n - 1);
    cout << endl;
    result_file << endl;

    return time_count;
}
void PrintParens(vector< vector<int> > s, int i, int j){
    if(i == j){
        cerr << "A" << i;
        result_file << "A" << i;
    }
    else{
        cerr << "(";
        result_file << "(";
        PrintParens(s, i, s[i][j]);
        PrintParens(s, s[i][j] + 1, j);
        cerr << ")";
        result_file << ")";
    }
}

int main(){
    const int data_len[4] = {5, 10, 20, 30};
    vector<int> data;
    GetSourceData(30, data);    // get 30 matrix data
    // open output file ctx
    if(!result_file.is_open() || !time_file.is_open()){
        cerr << "can't create output file: result.txt or time.txt" << endl;
        return -3;
    }
    // start cal
    for(int i = 0; i < 4; ++i)
        cout << "result for ordering " << data_len[i] << " matrix: " 
             <<  CalMatrixOrder(data_len[i] + 1, data) * 1E+6 << "us" << endl;
    result_file.close();
    time_file.close();
    return 0;
}