#include "lzq.h"
#include "graph.h"

int main(){
    std::string filename("../input/size1/input.txt");
    graph::Graph<int> g(filename, ',', 8, true, false);
    g.ShowDebugInfo();
}