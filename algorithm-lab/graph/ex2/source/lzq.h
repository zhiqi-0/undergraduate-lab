// Author: zhiqilin 
// Contacts: ralzq01@mail.ustc.edu.cn
// Version: 0.1
// Last update time: 2017-12-27

#ifndef _LZQ_H_
#define _LZQ_H_

#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstdio>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <random>
#include <algorithm>

namespace lzq{

template<typename T>
inline const bool CheckIsZero(const T& check_item, const std::string error_info){
    if(check_item){
        fprintf(stderr, error_info.c_str());
    }
    return !check_item;
}

template<typename T>
inline const bool CheckNotZero(const T& check_item, const std::string error_info){
   return CheckIsZero(!check_item, error_info);
}

template<typename T>
inline const bool CheckLessZero(const T& check_item, const std::string error_info){
    if(check_item >= 0){
        fprintf(stderr, error_info.c_str());
    }
    return check_item < 0;
}

// This class is used for counting time
class Timer{
 private:
    bool start_count_flag_;
    std::chrono::steady_clock::time_point start_;
    std::chrono::steady_clock::time_point end_;
 public:
    Timer():start_count_flag_(false) {}
    ~Timer() {}
    // Start counting time
    const bool StartCount(){
        if(start_count_flag_)
            return false;
        start_count_flag_ = true;
        start_ = std::chrono::steady_clock::now();
        return true;
    }
    // Stop counting time
    const bool StopCount(){
        if(!start_count_flag_)
            return false;
        start_count_flag_ = false;
        end_ = std::chrono::steady_clock::now();
        return true;
    }
    // Get time span after stop counting time
    const bool GetTimeSpan(double& seconds) const{
        if(start_count_flag_) return false;
        std::chrono::duration<double> time_span = 
        std::chrono::duration_cast<std::chrono::duration<double> > (end_ - start_);
        seconds = time_span.count();
        return true;
    }
    // reset the counter
    void Reset(){
        start_count_flag_ = false;
        return;
    }

};

template<typename T>
class ThreadSafeQueue{
 private:
    mutable std::mutex mu_;
    std::queue<T> queue_;
    std::condition_variable cond_;
 public:
    ThreadSafeQueue() {}
    ~ThreadSafeQueue() {}
    // add a new item into the queue
    void Push(T new_value) {
        mu_.lock();
        queue_.push(std::move(new_value));
        mu_.unlock();
        cond_.notify_all();
    }
    // wait until the queue is not empty and then pop the first item
    void WaitAndPop(T* value) {
        std::unique_lock<std::mutex> lk(mu_);
        cond_.wait(lk, [this]{return !queue_.empty();});
        *value = std::move(queue_.front());
        queue_.pop();
    }
};

class Random{
 public: 
    // get Random instance
    static Random* get(){
        static Random theRandom;
        return &theRandom;
    }
    // return integer range in [range_start, range_end]
    int RandomInt(int range_start, int range_end){
        int rand_var = rand()%(range_end - range_start + 1) + range_start;
        return rand_var;
    }
    // return float range from [range_start, range_end]
    float RandomFloat(int range_start, int range_end){
        float rand_var = (double)rand()/RAND_MAX;
        return rand_var * (range_end - range_start + 1) + range_start;
    }
    // random shuffle for a vector
    template<typename T>
    void VecShuffle(std::vector<T>& vec){
        std::shuffle(std::begin(vec), std::end(vec), rng_);
    }

 private:
    unsigned int seed_;
    std::default_random_engine rng_;
    Random(): seed_(time(NULL)), rng_(seed_) {srand(seed_);}
};



}   // namespace lzq

#endif