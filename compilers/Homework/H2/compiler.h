// Description: Simple Complier Implemetation
// Based on the book by Yu Zhang, Yiyun Chen, 3rd version
// Author: Zhiqi Lin PB15111672
// Last Update Time: 9-9-2017

#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <queue>

namespace compiler{

// Nfa Class.
// basic structure <current_state, input char, next_state set>
class NfaForm{
private:
    std::unordered_map<int, std::unordered_map<char, std::set<int> > > table_;
    int start_state_;
    std::set<int> end_state_;
public:
    NfaForm():start_state_(0) {}
    ~NfaForm() {}
    std::set<int>* GetMoveSet(int curr_state, char input){
        auto check_state = table_.find(curr_state);
        if(check_state == table_.end()) return NULL;
        auto check_input = check_state->second.find(input);
        if(check_input == check_state->second.end()) return NULL;
        return &check_input->second;
    }
    bool Find(int curr_state, char input, int next_state) const{
        auto check_state = table_.find(curr_state); 
        if(check_state == table_.end()) return false;
        auto check_input = check_state->second.find(input);
        if(check_input == check_state->second.end()) return false;
        auto check_next_state = check_input->second.find(next_state);
        if(check_next_state == check_input->second.end()) return false;
        return true;
    }
    void AddSet(int curr_state, char input, std::set<int> next_state_set){
        auto check_state = table_.find(curr_state);
        if(check_state == table_.end()){
            table_[curr_state][input] = next_state_set;
            return;
        }
        auto check_input = check_state->second.find(input);
        if(check_input == check_state->second.end()){
            table_[curr_state][input] = next_state_set;
            return;
        }
        table_[curr_state][input].insert(next_state_set.begin(), next_state_set.end());
        return;
    }
    const int GetStartState() const {return start_state_;}
    const std::set<int>& GetEndState() const {return end_state_;}
    const bool CheckIsEnd(int curr_state) const {
        return end_state_.find(curr_state) != end_state_.end();
    }
    void AddEndSet(int state) {end_state_.insert(state);}
};

// Compiler class. Singeletion Design Mode
class Compiler{
private:
    Compiler() {}                               // hidden constructor
    Compiler(Compiler const&);                  // forbidden copy
    Compiler& operator=(Compiler const&);       // forbidden assignment
    ~Compiler() {}                              // hidden disconstructor

    std::vector<std::string> regex_;            // regular expression vector
    std::string charstream_;                    // input charstream
    void SetNfa() {}
    void NfaToDfa() {}
    void SimplifyDfa() {}

public:
    NfaForm nfa_form_;

    static Compiler* Instance(){
        static Compiler the_compiler;
        return &the_compiler; 
    }
    void MatchNfa();
    bool MatchDfa() {return false;}
    void GetCharStream(std::string stream_) {
        charstream_.clear(); 
        charstream_ = std::string(stream_);
    }  
};

}   // namespace compiler

#endif