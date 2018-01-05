#include "lzq.h"
#include "graph.h"

int main(){
    const int datasize[6] = {8, 16, 32, 64, 128, 256};
    double timespan;
    lzq::Timer timer;
    for(int i = 0; i < 6; ++i){
        std::string filename = std::string("../input/size") + std::to_string(i + 1) + std::string("/input.txt");
        graph::Graph<int> g(filename, ',', datasize[i], true, false);

        timer.StartCount();
        std::vector<std::vector<int> > res = g.StrongConn();
        timer.StopCount();
        timer.GetTimeSpan(timespan);
        
        //return 0;
        //g.GraphvizView("test", true, false);

        std::string outfile = std::string("../output/size") + std::to_string(i + 1) + std::string("/output1.txt");
        std::ofstream outputfile(outfile);
        for(int i = 0; i < res.size(); ++i){
            outputfile << "slice" << i + 1 << ":\t";
            for(int j = 0; j < res[i].size(); ++j)
                outputfile << res[i][j] << '\t';
            outputfile << std::endl;
        }

        std::string timefilename = std::string("../output/size") + std::to_string(i + 1) + std::string("/time1.txt");
        std::ofstream timefile(timefilename);
        timefile << "Time cost: " << timespan * 1E+6 << "us" << std::endl;
        g.GraphvizView(std::string("../output/size") + std::to_string(i + 1), (i + 1) > 4 ? false : true, false);
    }
    return 0;
}