#include "compiler.h"

using namespace compiler;

void print_set(std::set<int> *set_){
    for(auto it = set_->begin(); it != set_->end(); ++it)
        fprintf(stdout, "%d, ", *it);
    std::cout << std::endl;
}

int main(){
    Compiler* ctx = Compiler::Instance();
    // test NfaForm Class
    NfaForm nfa;
    std::set<int> add_set;
    // add node and edge
    add_set.insert(1); add_set.insert(3);
    nfa.AddSet(0, 0, add_set); ctx->nfa_form_.AddSet(0, 0, add_set);
    add_set.clear(); add_set.insert(2);
    nfa.AddSet(1, 'a', add_set); ctx->nfa_form_.AddSet(1, 'a', add_set);
    add_set.clear(); add_set.insert(4);
    nfa.AddSet(3, 'b', add_set); ctx->nfa_form_.AddSet(3, 'b', add_set);
    add_set.clear(); add_set.insert(2);
    nfa.AddSet(2, 'a', add_set); ctx->nfa_form_.AddSet(2, 'a', add_set);
    add_set.clear(); add_set.insert(4);
    nfa.AddSet(4, 'b', add_set); ctx->nfa_form_.AddSet(4, 'b', add_set);
    // add end set
    nfa.AddEndSet(2); nfa.AddEndSet(4); ctx->nfa_form_.AddEndSet(2); ctx->nfa_form_.AddEndSet(4);
    // test Find & GetMoveSet
    /*if(!nfa.Find(0, 0, 1)) fprintf(stderr, "Error Wrong 1.\n");
    if(!nfa.Find(0, 0, 3)) fprintf(stderr, "Error Wrong 2.\n");
    if(!nfa.Find(1, 'a', 2)) fprintf(stderr, "Error Wrong 3.\n");
    if(!nfa.Find(2, 'a', 2)) fprintf(stderr, "Error Wrong 4.\n");
    if(!nfa.Find(3, 'b', 4)) fprintf(stderr, "Error Wrong 5.\n");
    if(!nfa.Find(4, 'b', 4)) fprintf(stderr, "Error Wrong 6.\n");
    if(nfa.Find(0, 0, 4)) fprintf(stderr, "Error Wrong 7.\n");
    if(nfa.Find(1, 'a', 4)) fprintf(stderr, "Error Wrong 8.\n");
    if(nfa.Find(2, 'b', 2)) fprintf(stderr, "Error Wrong 9.\n");
    auto res = nfa.GetMoveSet(0, 0); print_set(res);
    res = nfa.GetMoveSet(1, 'a'); print_set(res);
    res = nfa.GetMoveSet(2, 'a'); print_set(res);
    res = nfa.GetMoveSet(3, 'b'); print_set(res);
    res = nfa.GetMoveSet(4, 'b'); print_set(res);
    *res = nfa.GetEndState(); print_set(res);*/
    
    // test MatchNfa()
    char str[100];
    while(true){
        scanf("%s", str);
        if(str[0] == 'q') break;
        ctx->GetCharStream(str);
        ctx->MatchNfa();
    }

    return 0;

}