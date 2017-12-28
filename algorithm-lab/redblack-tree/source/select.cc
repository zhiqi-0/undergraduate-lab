#include <iostream>
#include <fstream>
#include <vector>

int Partition(int* array, int begin, int end){
    /* Partition the array from [begin, end] */
    int x = array[end];
    int i = begin - 1;
    for(int j = begin; j < end; ++j){
        if(array[j] < x){
            ++i;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[end]);
    return i + 1;
}

int Select(int* array, int begin, int end, int rank){
    if(begin == end)
        return array[begin];
    int q = Partition(array, begin, end);
    int k = q - begin + 1;
    if(rank == k)
        return array[q];
    else if(rank < k)
        return Select(array, begin, q - 1, rank);
    else
        return Select(array, q + 1, end, rank - k);
}

int main(){
    int array[60];
    std::ifstream infile("../input/input.txt");
    for(int i = 0; i < 60; ++i){
        infile >> array[i];
    }
    infile.close();

    const int selectsize[5] = {12, 24, 36, 48, 60};
    for(int i = 0; i < 5; ++i){
        int sel1 = selectsize[i] / 3;
        int sel2 = selectsize[i] / 4;
        std::cerr << "Selecting for data size " << selectsize[i] << ": "
                  << Select(array, 0, selectsize[i] - 1, sel1) << ','
                  << Select(array, 0, selectsize[i] - 1, sel2) << std::endl; 
    }
    return 0;
}