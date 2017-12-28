#ifndef _LZQ_SORT_H
#define _LZQ_SORT_H

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <climits>
#include "lzq.h"

#ifdef ProgressBar
inline void Tips(int i, int len){
    if(len < 10) return;
    int part = len / 10;
    if(i % part == 0){
        /* what is intersting is that std::cout has a buffer to output the content.
         * the content won't be printed onto screen until there is a \n or overflow.
         * So in this case if we use std::cout, there won't be any output until the
         * task is finished.(At last there is a \n). However, std::cerr doesn't have
         * any buffer so it will print the content immediatelly.
         */
        if(i / part > 10) return;
        std::cerr << i / part * 10 << "%...";
    }
    if(i == part * 10)
        std::cout << std::endl; 
}
#endif

template<typename T>
void PrintArray(T* array, int length){
    for(int i = 0; i < length; ++i)
        std::cout << array[i] << std::endl;
}

// ---------------------------------- BubbletSort ------------------------------------------
template<typename T>
void BubbleSort(T* array, int length, bool (*Compare)(T&, T&)){
    int i,j;
    for(i = 0; i < length; ++i){
        #ifdef ProgressBar
            Tips(i, length);
        #endif
        int end = length - 1 - i;
        for(j = 0; j < end; ++j){
            if(!(*Compare)(array[j], array[j + 1]))
                std::swap(array[j],array[j + 1]);
        }
    }
}
// ---------------------------------- BubbleSort ------------------------------------------

// ---------------------------------- InsertSort ------------------------------------------
template<typename T>
void InsertSort(T* array, int length, bool (*Compare)(T&, T&)){
    T key;
    int i, j;
    for(i = 1; i < length; ++i){
        #ifdef ProgressBar
            Tips(i, length);
        #endif
        key = array[i];
        j = i - 1;
        while(j >= 0 && !(*Compare)(array[j], key)){
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}
// ---------------------------------- InsertSort ------------------------------------------

// ---------------------------------- HeapSort ------------------------------------------
template<typename T>
void MaxHeapify(T* array, int i, int heapsize, bool (*Compare)(T&, T&)){
    int l = 2 * i + 1; // left child
    int r = 2 * i + 2; // right child
    int largest = i;
    if(l < heapsize && !(*Compare)(array[l], array[i]))
        largest = l;
    if(r < heapsize && !(*Compare)(array[r], array[largest]))
        largest = r;
    if(largest != i){
        std::swap(array[i], array[largest]);
        MaxHeapify(array, largest, heapsize, Compare);
    }
}
template<typename T>
void HeapSort(T* array, int length, bool (*Compare)(T&, T&)){
    /* build heap */ 
    int heapsize = length;
    for(int i = (heapsize - 1) / 2; i >= 0; --i)
        MaxHeapify(array, i, heapsize, Compare);
    /* get the maxium in every iteration */
    for(int i = heapsize - 1; i >= 1; --i){
        #ifdef ProgressBar
            Tips(length - 1 - i, length);
        #endif
        std::swap(array[0], array[i]);
        --heapsize;
        MaxHeapify(array, 0, heapsize, Compare);
    }
}
// ---------------------------------- HeapSort ------------------------------------------

// ---------------------------------- QuickSort ------------------------------------------
template<typename T>
int Partition(T* array, int begin, int end, bool (*Compare)(T&, T&)){
    /* Partition the array from [begin, end] */
    T x = array[end];
    int i = begin - 1;
    for(int j = begin; j < end; ++j){
        if((*Compare)(array[j], x)){
            ++i;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[end]);
    return i + 1;
}
template<typename T>
void QuickSort_(T* array, int begin, int end, bool (*Compare)(T&, T&)){
    if(begin >= end) return;
    int div = Partition(array, begin, end, Compare);
    QuickSort_(array, begin, div - 1, Compare);
    QuickSort_(array, div, end, Compare);
}
template<typename T>
void QuickSort(T* array, int length, bool (*Compare)(T&, T&)){
    QuickSort_(array, 0, length - 1, Compare);
}
// ---------------------------------- QuickSort ------------------------------------------

// ---------------------------------- MergeSort ------------------------------------------
template<typename T>
void Merge(T* array, int begin, int mid, int end, bool (*Compare)(T&, T&)){
    int len1 = mid - begin + 1;
    int len2 = end - mid;
    std::string *ptrl1 = new std::string[len1];
    std::string *ptrl2 = new std::string[len2];
    for(int i = 0; i < len1; ++i)
        ptrl1[i] = array[begin + i];
    for(int i = 0; i < len2; ++i)
        ptrl2[i] = array[mid + 1 + i];
    int l1 = 0, l2 = 0, k = begin;
    while(l1 < len1 && l2 < len2){
        if((*Compare)(ptrl1[l1], ptrl2[l2]))
            array[k++] = ptrl1[l1++];
        else
            array[k++] = ptrl2[l2++];
    }
    while(l1 < len1){
        array[k++] = ptrl1[l1++];
    }
    while(l2 < len2){
        array[k++] = ptrl1[l2++];
    }
    delete[] ptrl1; delete[] ptrl2;
}
template<typename T>
void MergeSort_(T* array, int begin, int end, bool (*Compare)(T&, T&)){
    if(begin >= end) return;
    int mid = (begin + end) / 2;
    MergeSort_(array, begin, mid, Compare);
    MergeSort_(array, mid + 1, end, Compare);
    Merge(array, begin, mid, end, Compare);
}
template<typename T>
void MergeSort(T* array, int length, bool (*Compare)(T&, T&)){
    MergeSort_(array, 0, length -1, Compare);
}
// ---------------------------------- MergeSort ------------------------------------------

// ---------------------------------- CountingSort ---------------------------------------
// Only suitable for sorting integer ranging from [range_begin, range_end]
void CountingSort(int* array, int length, int range_begin, int range_end){
    std::size_t range = range_end - range_begin + 1;
    int* res = new int[length];
    int* C = new int[range];
    memset(C, 0, range * sizeof(int));
    // count equal
    for(int i = 0; i < length; ++i)
        ++C[array[i] - range_begin];

    #ifdef ProgressBar
        std::cerr << "30%...";
    #endif
    // count small
    for(int i = 1; i < range; ++i)
        C[i] += C[i - 1];

    #ifdef ProgressBar
        std::cerr << "60%...";
    #endif
    // put number into right position
    for(int j = length - 1; j >= 0; --j){
        res[C[array[j] - range_begin] - 1] = array[j];
        --C[array[j] - range_begin];
    }

    #ifdef ProgressBar
        std::cerr << "95%...\n";
    #endif

    memcpy(array, res, length * sizeof(int));
    delete[] C; delete[] res;
}
// ---------------------------------- CountingSort ---------------------------------------

// ---------------------------------- RadixSort ------------------------------------------
// Only suitable for sorting integer
void RadixSort(int* array, int length, int nbit){
    int* res = new int[length];
    // base 0x, use Counting sort
    const int base = 16;
    int C[base];
    // ceil integer
    int numiter = (nbit - 1) / 4 + 1;
    // store unhandled section and remainder
    int* remainder = new int[length];
    for(int iter = 0; iter < numiter; ++iter){
        #ifdef ProgressBar
            Tips(iter, numiter);
        #endif
        for(int i = 0; i < length; ++i)
            remainder[i] = (array[i] >> (4 * iter)) % base;
        // Counting Sort
        memset(C, 0, base * sizeof(int));
        for(int i = 0; i < length; ++i)
            ++C[remainder[i]];
        for(int i = 1; i < base; ++i)
            C[i] += C[i - 1];
        for(int i = length - 1; i >= 0; --i)
            res[C[remainder[i]]-- - 1] = array[i];
        memcpy(array, res, length * sizeof(int));
    }
    delete[] remainder; delete[] res;
}
// ---------------------------------- RadixSort ------------------------------------------

#endif
