#include "compiler.h"

namespace compiler{

void Compiler::MatchNfa(){
    bool match = false;
    int iter = 0, str_len = charstream_.size();
    std::set<int> *state;
    std::vector<int> reach_node;
    int curr_state_num = 1;
    int start = 0;

    reach_node.push_back(nfa_form_.GetStartState()); 
    while(iter < str_len){
        // Add all reachable node (empty char) into the set.
        for(int i = 0 ; i < reach_node.size(); ++i){
            state = nfa_form_.GetMoveSet(reach_node[i], 0);
            if(!state) continue;
            for(auto it = state->begin(); it != state->end(); ++it){
                if(std::find(reach_node.begin(), reach_node.end(), *it) == reach_node.end()){
                    reach_node.push_back(*it);
                    ++curr_state_num;
                }
            }
        }
        // Check whether this state can get out
        for(auto it = reach_node.begin(); it != reach_node.end(); ++it)
            if(nfa_form_.CheckIsEnd(*it)) match = true;

        // Find the suitable move state for input char
        for(int i = 0; i < curr_state_num; ++i){
            state = nfa_form_.GetMoveSet(reach_node[i], charstream_[iter]);
            if(state){
                for(auto it = state->begin(); it != state->end(); ++it){
                    if(std::find(reach_node.begin() + curr_state_num, reach_node.end(), *it) == reach_node.end())
                        reach_node.push_back(*it);
                }
            }
        }
        reach_node.erase(reach_node.begin(), reach_node.begin() + curr_state_num);
        curr_state_num = reach_node.size();
        if(!curr_state_num){
            if(match == true)
                std::cout << charstream_.substr(start, iter - start) << std::endl;
            if(start == iter){
                start = iter + 1;
            }
            else{       // back from wrong status
                start = iter; --iter;
            }
            curr_state_num = 1;
            reach_node.push_back(nfa_form_.GetStartState());
        }
        match = false;
        ++iter;
    }
    for(auto it = reach_node.begin(); it != reach_node.end(); ++it)
        if(nfa_form_.CheckIsEnd(*it))
            std::cout << charstream_.substr(start, iter - start + 1) << std::endl;
}

}   // namespace compiler