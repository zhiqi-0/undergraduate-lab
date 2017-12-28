#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "redblacktree.h"

//template RedBlackTree<int>;

int main(){
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    std::vector<int> key_array(&array[0], &array[10]);
    auto rng = std::default_random_engine((unsigned)time(NULL));
    /************* test for insert ************/
    for(int i = 0; i < 5; ++i){
        std::shuffle(std::begin(key_array), std::end(key_array), rng);
        std::cerr << "Insert key array: ";
        for(auto e : key_array){
            std::cerr << e << ',';
        }
        std::cerr << std::endl;
        RedBlackTree<int> rbtree(key_array);
        rbtree.print();
        std::shuffle(std::begin(key_array), std::end(key_array), rng);
        std::cerr << "Delete key: ";
        for(auto e : key_array){
            std::cerr << e << std::endl;//' ';
            rbtree.Delete(e);
            rbtree.print();
        }
        std::cerr << std::endl;
    }
    /************* debug ***************/
    /*int debug[10] = {6,7,5,1,9,4,2,3,10,8};
    std::vector<int> test(&debug[0], &debug[10]);
    RedBlackTree<int> rbtree(test);
    for(auto e : test){
        std::cerr << "Insert Key: " << e << std::endl;
        rbtree.Insert(e);
        rbtree.print();
    }*/
    
    /*RedBlackTree<int> rbtree(std::vector<int>(&debug[0], &debug[10]));
    rbtree.print();
    rbtree.Delete(6);
    rbtree.print();
    rbtree.Delete(7);
    rbtree.print();
    rbtree.Delete(5);
    rbtree.print();
    rbtree.Delete(1);
    rbtree.print();*/
    return 0;
}
