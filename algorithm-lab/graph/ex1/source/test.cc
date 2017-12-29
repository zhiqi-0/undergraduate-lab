#include "lzq.h"
#include "graph.h"

int main(){
    std::string filename("../input/size1/input.txt");
    graph::Graph<int> g(filename, ',', 8, true, false);
    g.ShowGraphInfo();
    std::vector<std::vector<int> > res = g.StrongConn();
    for(int i = 0; i < res.size(); ++i){
        for(int j = 0; j < res[i].size(); ++j)
            std::cout << res[i][j] << '\t';
        std::cout << std::endl;
    }
    //g.ShowDebugInfo();
}