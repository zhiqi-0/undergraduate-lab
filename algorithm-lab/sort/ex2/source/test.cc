#include "sort.h"
#include <fstream>
#include <sstream>

using namespace std;

lzq::Timer timer;
double spantime_s; //seconds
ifstream datafile;
ofstream outfile;
string* str;
int* intarray;

/* StrComapare(a,b)
 * if a <= b return true else false
 */
inline bool StrCompare(std::string& a, std::string& b){
    if(a.size() < b.size()) return true;
    else if(a.size() > b.size()) return false;
    else return a <= b;
}

inline bool IntCompare(int& a, int& b){
    return a <= b;
}

// Reading Data
void GetData(string datatype, string alg, size_t len){
    if(datatype == string("str")){
        datafile = ifstream("../input/input_strings.txt");
        for(int i = 0; i < len; ++i)
            getline(datafile, str[i]);
    }
    else if(datatype == string("int")){
        datafile.open("../input/input_ints.txt");
        for(int i = 0; i < len; ++i)
            datafile >> intarray[i];
    }     
    else{
        cerr << "Unknown DataType" << endl;
        exit(1);
    }
    datafile.close();
    cout << endl << "Start Sorting: " << "Algorithm: " << alg << endl;
    timer.StartCount();
}
// Write Data
void WriteData(char** argv, size_t len, string alg){
    // test time data
    timer.StopCount(); timer.GetTimeSpan(spantime_s);
    cout << "Algorithm: " << alg << " Data Size: 1 << " << len << ", Sort Time Span: " 
         << spantime_s << " s" << endl;
    string filedir = string("../output/") + alg + string("/time.txt");
    ofstream outfile(filedir, ios::app | ios::out);
    outfile << len << " : " << spantime_s << endl;
    outfile.close();
    // put res into file
    stringstream ss;
    ss << len;
    string len_str;
    ss >> len_str;
    filedir = string("../output/") + alg + string("/result_") + len_str + string(".txt");
    outfile = ofstream(filedir);
    if(string(argv[1]) == string("int")){
        for(int i = 0; i < (1 << len); ++i)
            outfile << intarray[i] << endl;
    }
    else if(string(argv[1]) == string("str")){
        for(int i = 0; i < (1 << len); ++i)
            outfile << str[i] << endl;
    }
    outfile.close();
}

int main(int argc, char** argv){
    if(argc != 2){ // "str or int"
        cerr << "Please give 2 parameters:\n datatype: str or int\n data num: 2 or 5 or 8 or 11 or 14 or 17\n";
        return -1;
    }
    for(int i = 2; i <= 17; i+=3){
        int len = 1 << i;
        if(string(argv[1]) == string("str")){
            str = new string[len];
            // ------------------------------------------ InsertSort Evaluation ------------------------------------
            GetData(string(argv[1]), string("InsertSort"), len);
            InsertSort(str, len, StrCompare);
            WriteData(argv, i, "InsertSort");
            // ------------------------------------------ InsertSort Evaluation ------------------------------------
            // ------------------------------------------ HeapSort Evaluation --------------------------------------
            GetData(string(argv[1]), string("HeapSort"), len);
            HeapSort(str, len, StrCompare);
            WriteData(argv, i, "HeapSort");
            // ------------------------------------------ HeapSort Evaluation --------------------------------------
            // ------------------------------------------ MergeSort Evaluation -------------------------------------
            GetData(string(argv[1]), string("MergeSort"), len);
            MergeSort(str, len, StrCompare);
            WriteData(argv, i, "MergeSort");
            // ------------------------------------------ MergeSort Evaluation -------------------------------------
            // ------------------------------------------ QuickSort Evaluation -------------------------------------
            GetData(string(argv[1]), string("QuickSort"), len);
            QuickSort(str, len, StrCompare);
            WriteData(argv, i, "QuickSort");
            // ------------------------------------------ QuickSort Evaluation -------------------------------------
            delete[] str;
        }
        else if(string(argv[1]) == string("int")){
            intarray = new int[len];
            // ------------------------------------------ BubbleSort Evaluation ------------------------------------
            GetData(string(argv[1]), string("BubbleSort"), len);
            BubbleSort(intarray, len, IntCompare);
            WriteData(argv, i, "BubbleSort");
            // ------------------------------------------ BubbleSort Evaluation ------------------------------------
            // ------------------------------------------ QuickSort Evaluation -------------------------------------
            GetData(string(argv[1]), string("QuickSort"), len);
            QuickSort(intarray, len, IntCompare);
            WriteData(argv, i, "QuickSort");
            // ------------------------------------------ QuickSort Evaluation -------------------------------------
            // ------------------------------------------ RadixSort Evaluation -------------------------------------
            GetData(string(argv[1]), string("RadixSort"), len);
            RadixSort(intarray, len, 16);
            WriteData(argv, i, "RadixSort");
            // ------------------------------------------ RadixSort Evaluation -------------------------------------
            // ------------------------------------------ CountingSort Evaluation ----------------------------------
            GetData(string(argv[1]), string("CountingSort"), len);
            CountingSort(intarray, len, 1, 65535);
            WriteData(argv, i, "CountingSort");
            // ------------------------------------------ CountingSort Evaluation ----------------------------------
            delete[] intarray;
        }
        else{
            cerr << "Unknown Parameter 1. Please Enter str or int" << endl;
            return 1;
        }  
    }
    return 0;
}