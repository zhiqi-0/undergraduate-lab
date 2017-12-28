
#include <iostream>
#include <fstream>
#include "lzq.h"
#include "redblacktree.h"

std::vector<int> GetData(){
    std::ifstream inputfile("../input/input.txt");
    std::vector<int> data;
    int tmp;
    for(int i = 0; i < 60; ++i){
        inputfile >> tmp;
        data.push_back(tmp);
    }
    inputfile.close();
    return data;
}

void TestBuild(std::vector<int>& data, std::size_t size){
    // insert data to a empty rbtree
    RedBlackTree<int> rbtree(std::vector<int>(&data[0], &data[size]));
    // Timer stop
    // get preorder, inorder, postorder vector
    std::vector<int> preorder = rbtree.OrderPass("preorder");
    std::vector<int> inorder = rbtree.OrderPass("inorder");
    std::vector<int> postorder = rbtree.OrderPass("postorder");
    // record result
    std::ofstream prefile, infile, postfile;
    prefile.open("../output/preorder.txt", std::ios::app);
    infile.open("../output/inorder.txt", std::ios::app);
    postfile.open("../output/postorder.txt", std::ios::app);
    if(!prefile.is_open() || !infile.is_open() || !postfile.is_open()){
        std::cerr << "Error in opening result file" << std::endl;
        exit(1);
    }
    // write result into files
    prefile << "data size: " << size << " :\n";
    infile << "data size: " << size << " :\n";
    postfile << "data size: " << size << " :\n";
    for(unsigned i = 0; i < size; ++i){
        prefile << preorder[i] << ' ';
        infile << inorder[i] << ' ';
        postfile << postorder[i] << ' ';
    }
    prefile << std::endl;
    infile << std::endl;
    postfile << std::endl;
    prefile.close();
    infile.close();
    postfile.close();
}

void TestInsertTime(std::vector<int>& data){
    double total_time = 0;
    RedBlackTree<int> rbtree;
    std::ofstream timefile("../output/time1.txt");
    timefile << "Every 10 number inserting time(us):" << std::endl;
    lzq::Timer timer; double timespan;
    timer.StartCount();
    for(int i = 1; i <= 60; ++i){
        rbtree.Insert(data[i]);
        if(i % 10 == 0){
            timer.StopCount();
            timer.GetTimeSpan(timespan);
            timefile << timespan * 1E+6 << " us" << std::endl;
            total_time += timespan * 1E+6;
            timer.StartCount();
        }
    }
    timer.StopCount();
    timefile << "Total Time(us): " << total_time << " us" << std::endl;
    timefile.close();
}

void TestDelete(std::vector<int>& data, std::size_t size){
    RedBlackTree<int> rbtree(std::vector<int>(&data[0], &data[size]));
    std::ofstream delfile("../output/delete_data.txt", std::ios::app);
    std::size_t delnode1 = size / 3, delnode2 = size / 4;
    auto node1 = rbtree.Select(delnode1, rbtree.getRoot());
    auto node2 = rbtree.Select(delnode2, rbtree.getRoot());
    delfile << "rbtree size " << size << " , delete: "
            << node1->key_ << ',' << node2->key_ << std::endl;
    delfile.close();
    // Start Counting
    lzq::Timer timer; double timespan; double total_time = 0;
    timer.StartCount();
    //firset delete
    rbtree.Delete(node1->key_);
    timer.StopCount();
    timer.GetTimeSpan(timespan);

    std::ofstream timefile("../output/time2.txt", std::ios::app);
    timefile << "rbtree size " << size << ": " << timespan * 1E+6 << " us, ";
    total_time += timespan * 1E+6;
    timer.StartCount();
    // second delete
    rbtree.Delete(node2->key_);
    timer.StopCount();
    timer.GetTimeSpan(timespan);
    timefile << timespan * 1E+6 << " us, total time: ";

    total_time += timespan * 1E+6;
    timefile << total_time << " us" << std::endl;
    timefile.close(); 
}

int main(){
    std::vector<int> data = GetData();
    const int buildsize[5] = {12, 24, 36, 48, 60};
    for(int i = 0 ; i < 5; ++i){
        TestBuild(data, buildsize[i]);
        TestDelete(data, buildsize[i]);
    }
    TestInsertTime(data);
    return 0;
}