#ifndef _MEAN_HEAP_LZQ_H_
#define _MEAN_HEAP_LZQ_H_

#include<iostream>
#include<vector>
#include<cstdlib>
#include "lzq.h"

namespace heap{

template<typename T>
class MinHeap{
 public:
    MinHeap(): minheap_(0) {}
    MinHeap(std::vector<T> init);
    inline T getMin() {return minheap_[0];};
    T ExtractMin();
    void Insert(T key);
    int SearchKey(T key);
    void ResetKey(T old_key, T new_key);
    void Show();
    
 private:
    std::vector<T> minheap_;
    inline int Parent(int i) {return (i - 1) >> 1;}
    inline int Lchild(int i) {return (i << 1) + 1;}
    inline int Rchild(int i) {return (i << 1) + 2;}
    void MinHeapify(int i);
};

template<typename T>
MinHeap<T>::MinHeap(std::vector<T> init): minheap_(init){
    for(int i = Parent(init.size() - 1); i >= 0; --i){
        MinHeapify(i);
    }
}

template<typename T>
void MinHeap<T>::MinHeapify(int i){
    int smallest = i;
    if(Lchild(i) < minheap_.size() && minheap_[Lchild(i)] < minheap_[smallest])
        smallest = Lchild(i);
    if(Rchild(i) < minheap_.size() && minheap_[Rchild(i)] < minheap_[smallest])
        smallest = Rchild(i);
    if(smallest != i){
        std::swap(minheap_[i], minheap_[smallest]);
        MinHeapify(smallest);
    }
}

template<typename T>
T MinHeap<T>::ExtractMin(){
    T res = getMin();
    std::swap(minheap_[0], minheap_[minheap_.size() - 1]);
    minheap_.pop_back();
    MinHeapify(0);
    return res;
}

template<typename T>
void MinHeap<T>::Insert(T key){
    minheap_.push_back(key);
    int pos = minheap_.size() - 1;
    while(Parent(pos) >= 0 && minheap_[pos] < minheap_[Parent(pos)]){
        std::swap(minheap_[pos], minheap_[Parent(pos)]);
        pos = Parent(pos);
    }
}

template<typename T>
int MinHeap<T>::SearchKey(T key){
    for(int pos = 0; pos < minheap_.size(); ++pos)
        if(minheap_[pos] == key)
            return pos;
    return -1;
}

template<typename T>
void MinHeap<T>::ResetKey(T old_key, T new_key){
    int pos = SearchKey(old_key);
    if(pos < 0){
        std::cout << "Can't find old key" << std::endl;
        exit(1);
    }
    minheap_[pos] = new_key;
    if(new_key < old_key){
        while(Parent(pos) >= 0 && minheap_[pos] < minheap_[Parent(pos)]){
            std::swap(minheap_[pos], minheap_[Parent(pos)]);
            pos = Parent(pos);
        }
    }
    else
        MinHeapify(pos);
}

template<typename T>
void MinHeap<T>::Show(){
    int pos = 0;
    int row_num = 1;
    int next_row_num = 2;
    while(pos < minheap_.size()){
        std::cout << minheap_[pos];
        pos += 1;
        row_num -= 1;
        if(row_num == 0){
            row_num = next_row_num;
            next_row_num = row_num << 1;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}




} // namespace heap

#endif