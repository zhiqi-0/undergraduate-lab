#include "graph.h"

int main(){
    const int datasize[6] = {8, 16, 32, 64, 128, 256};
    double timespan;
    lzq::Timer timer;
    for(int i = 0; i < 6; ++i){
        std::string filename = std::string("../input/size") + std::to_string(i + 1) + std::string("/input.txt");
        graph::Graph<int> g(filename, ',', datasize[i], false, true);

        timer.StartCount();
        auto res = g.Johnson();
        timer.StopCount();
        timer.GetTimeSpan(timespan);

        std::string outfile = std::string("../output/size") + std::to_string(i + 1) + std::string("/output1.txt");
        std::ofstream outputfile(outfile);

        auto nodelen = std::get<0>(res);
        auto nodepath = std::get<1>(res);
        // shortest length info
        outputfile << "shortest distance matrix:\n";
        std::size_t vertex_num = nodelen.size();
        outputfile << ' ' << '\t';
        for(unsigned i = 0; i < vertex_num; ++i)
            outputfile << i << '\t';
        outputfile << std::endl;
        for(unsigned i = 0; i < vertex_num; ++i){
            outputfile << i << '\t';
            for(unsigned j = 0; j < vertex_num; ++j){
                if(nodelen[i][j] == INT_MAX)
                    outputfile << "--\t";
                else
                    outputfile << nodelen[i][j] << '\t';
            }
            outputfile << std::endl;
        }
        // shortest path
        outputfile << "shortest path route:\n";
        for(int i = 0; i < vertex_num; ++i){
            for(int j = 0; j < vertex_num; ++j){
                outputfile << "Vertex " << i << " to " << j << ": ";
                for(auto path_node : nodepath[i][j]){
                    outputfile << path_node << ' ';
                }
                outputfile << std::endl;
            }
        }

        std::string timefilename = std::string("../output/size") + std::to_string(i + 1) + std::string("/time1.txt");
        std::ofstream timefile(timefilename);
        timefile << "Time cost: " << timespan * 1E+6 << "us" << std::endl;
        g.GraphvizView(std::string("../output/size") + std::to_string(i + 1), (i + 1) > 3 ? false : true, false);
    }
    return 0;
}