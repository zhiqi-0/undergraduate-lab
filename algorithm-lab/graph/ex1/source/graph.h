#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <fstream>
#include <cstdlib>

#ifndef LZQ_GRAPH_H_
#define LZQ_GRAPH_H_

namespace graph{

const int NoEdge = INT_MAX;

enum VisitColor{White = 0, Grey, Black};

template<typename T>
class GraphNode{
 public:
    T attr_;
    GraphNode() {}
    GraphNode(T attr): attr_(attr) {}
};

struct VisitInfo{
    int start_time;
    int end_time;
    int parent;
    VisitColor color;
    VisitInfo(): start_time(0), end_time(0), parent(0), color(VisitColor::White) {}
};

template<typename T>
class Graph{
 private:
    std::vector<std::vector<int> > matrix_;
    std::vector<GraphNode<T> > node_info_;
    std::vector<VisitInfo> visit_info_;

    void DfsVisit(int node, int time);
 public:
    Graph(std::string filename, char parser, std::size_t vertex_num, bool direct = true, bool have_weight = true);
    Graph() {};
    void VisitReset();
    std::vector<std::vector<int> > StrongConn();
    void Dfs();
    // output information
    void ShowGraphInfo();
    void ShowVisitInfo();
    void ShowDebugInfo();
};

template<typename T>
Graph<T>::Graph(std::string filename, char parser, std::size_t vertex_num, bool direct, bool have_weight):
        matrix_(std::vector<std::vector<int> >(vertex_num, std::vector<int>(vertex_num, NoEdge))),
        node_info_(std::vector<GraphNode<T> >(vertex_num)),
        visit_info_(std::vector<VisitInfo>(vertex_num)){
    std::ifstream datafile(filename);
    if(!datafile.is_open()){
        std::cerr << "data file open fail. Initiate graph fail." << std::endl;
        exit(1);
    }
    char read_parser = 0;
    int vertex1, weight = 1, vertex2;
    while(datafile.peek()!= EOF && datafile.good()){
        datafile >> vertex1;
        do{
            datafile >> read_parser;
        }while(read_parser != parser);

        if(have_weight){
            datafile >> weight;
            do{
                datafile >> read_parser;
            }while(read_parser != parser);
        }

        datafile >> vertex2;
        if(vertex1 >= vertex_num || vertex2 >= vertex_num){
            std::cout << "initial data error, vertex can't be greater or equal to vertex_num\n";
            exit(2);
        }
        // there need more check: nan & parser & EOF check
        if(direct)
            matrix_[vertex1][vertex2] = 1;
        else
            matrix_[vertex1][vertex2] = matrix_[vertex2][vertex1] = weight;
    }
    datafile.close();
}

template<typename T>
void Graph<T>::DfsVisit(int node, int visit_time){
    visit_time = visit_time + 1;
    visit_info_[node].start_time = visit_time;
    visit_info_[node].color = VisitColor::Grey;
    for(int i = 0; i < matrix_[node].size(); ++i){
        if(matrix_[node][i] != NoEdge &&
           visit_info_[i].color == VisitColor::White){
            visit_info_[i].parent = node;
            DfsVisit(i, visit_time);
        }
    }
    visit_info_[node].color = VisitColor::Black;
    visit_time += 1;
    visit_info_[node].end_time = visit_time;
}

template<typename T>
void Graph<T>::Dfs(){
    int visit_time = 0;
    for(int i = 0; i < node_info_.size(); ++i){
        if(visit_info_[i].color == VisitColor::White)
            DfsVisit(i, visit_time);
    }
}

template<typename T>
void Graph<T>::ShowGraphInfo(){
    std::size_t vertex_num = matrix_.size();

    std::cout << ' ' << '\t';
    for(unsigned i = 0; i < vertex_num; ++i)
        std::cout << i << '\t';
    std::cerr << std::endl;

    for(unsigned i = 0; i < vertex_num; ++i){
        std::cout << i << '\t';
        for(unsigned j = 0; j < vertex_num; ++j){
            if(matrix_[i][j] == NoEdge)
                std::cout << "--\t";
            else
                std::cout << matrix_[i][j] << '\t';
        }
        std::cout << std::endl;
    }
}

template<typename T>
void Graph<T>::ShowVisitInfo(){
    std::size_t vertex_num = matrix_.size();
    for(unsigned i = 0; i < vertex_num; ++i){
        std::cout << "vertex: " << i << '\t';
        std::cout << "start time: " << visit_info_[i].start_time << '\t';
        std::cout << "end time: " << visit_info_[i].end_time << '\t';
        std::cout << "visit color: ";
        switch(visit_info_[i].color){
            case VisitColor::White:
                std::cout << "White"; break;
            case VisitColor::Grey:
                std::cout << "Grey"; break;
            case VisitColor::Black:
                std::cout << "Black"; break;
            default:
                std::cout << "Unknown";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void Graph<T>::ShowDebugInfo(){
    std::size_t vertex_num = matrix_.size();
    std::cout << "Graph vertex size: " << vertex_num << std::endl;

    std::cout << "Graph basic info:" << std::endl;
    ShowGraphInfo();

    std::cout << "Graph visit info:" << std::endl;
    ShowVisitInfo();
}

} // namespace graph

#endif