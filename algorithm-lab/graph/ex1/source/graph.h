#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <string>
#include <fstream>
#include <cstdlib>
#include <tuple>
#include <algorithm>
#include "lzq.h"

#ifndef LZQ_GRAPH_H_
#define LZQ_GRAPH_H_

namespace graph{

template<typename E>
using Adj = std::vector<std::list<E> >;

enum VisitColor{White = 0, Grey, Black};

template<typename T>
class Vertex{
 public:
    int order_;
    T attr_;
    VisitColor color_;
    int start_time_;
    int end_time_;
    int parent_;
    Vertex(int order = 0): order_(order), start_time_(0), end_time_(0), parent_(0), color_(VisitColor::White) {}
    Vertex(T attr, int order): order_(order), start_time_(0), end_time_(0), parent_(0), color_(VisitColor::White), attr_(attr) {}
};

template<typename V>
class Graph{
 private:
    // Adjacy table stores vertex order & edge weight
    Adj<std::tuple<int, int> > adj_;
    std::vector<Vertex<V> > node_list_;
    void DfsVisit(int node, int& time, std::vector<int>& conn, Adj<std::tuple<int, int> >* p_adj = nullptr);
    void DeEndDfsVisit(std::vector<std::vector<int> >& matrix, int node, std::vector<int>& strong_conn);

 public:
    // file initializer
    Graph(std::string filename, char parser, std::size_t vertex_num, bool direct = true, bool have_weight = true);
    // default initializer, init an empyt graph
    Graph() {};
    void inline VisitReset();
    void inline ColorReset();

    // basic info
    inline bool setEdgeWeight(int vertex1, int vertex2, int weight);
    inline int* findEdge(int vertex1, int vertex2);

    std::vector<std::vector<int> > StrongConn();
    std::vector<std::vector<int> > Dfs();
    // output information
    void ShowGraphInfo();
    void ShowVisitInfo();
    void ShowDebugInfo();
    void GraphvizView(std::string filename, bool dump_png, bool dump_svg);
};

template<typename V>
Graph<V>::Graph(std::string filename, char parser, std::size_t vertex_num, bool direct, bool have_weight):
        adj_(vertex_num),
        node_list_(std::vector<Vertex<V> >(vertex_num)){

    std::ifstream datafile(filename);
    if(!datafile.is_open()){
        std::cerr << "data file open fail. Initiate graph fail." << std::endl;
        exit(1);
    }
    // initialize vertex list
    for(int i = 0; i < vertex_num; ++i)
        node_list_[i] = Vertex<V>(i);
    
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
        setEdgeWeight(vertex1, vertex2, weight);
        if(!direct)
            setEdgeWeight(vertex2, vertex1, weight);
    }
    datafile.close();
}

template<typename V>
void Graph<V>::VisitReset(){    // trouble
    for(int i = 0; i < node_list_.size(); ++i){
        node_list_[i].start_time_ = node_list_[i].end_time_ = node_list_[i].parent_ = 0;
    }
}

template<typename V>
void Graph<V>::ColorReset(){
    for(int i = 0; i < node_list_.size(); ++i){
        node_list_[i].color_ = VisitColor::White;
    }
}

// if (vertex1, vertex2) doesn't exist, then make a edge with weight provided
// only when vertex1 or vertex2 out of range, the function will do nothing then return false
// should raise an exception
template<typename V>
bool Graph<V>::setEdgeWeight(int vertex1, int vertex2, int weight){
    if(vertex1 >= adj_.size() || vertex2 >= adj_.size()){
        std::cerr << "Wrong set edge weight. Vertex order wrong." << std::endl;
        return false;
    }
    for(auto e = adj_[vertex1].begin(); e != adj_[vertex1].end(); e++){
        if(std::get<0>(*e) == vertex2){
            std::get<1>(*e) = weight;
            return true;
        }
    }
    adj_[vertex1].push_back(std::make_tuple(vertex2, weight));
    return true;
}

template<typename V>
int* Graph<V>::findEdge(int vertex1, int vertex2){
    for(auto e = adj_[vertex1].begin(); e != adj_[vertex1].end(); e++){
        if(std::get<0>(*e) == vertex2)
            return &std::get<1>(*e);
    }
    return nullptr;
}


template<typename V>
void Graph<V>::DfsVisit(int node, int &visit_time, std::vector<int>& conn, Adj<std::tuple<int, int> >* p_adj){
    Adj<std::tuple<int, int> >* adj;
    adj = p_adj ? p_adj : &adj_;
    conn.push_back(node);
    visit_time = visit_time + 1;
    node_list_[node].start_time_ = visit_time;
    node_list_[node].color_ = VisitColor::Grey;
    for(auto iter = (*adj)[node].begin(); iter != (*adj)[node].end(); ++iter){
        int i = std::get<0>(*iter);
        if(node_list_[i].color_ == VisitColor::White){
            node_list_[i].parent_ = node;
            DfsVisit(i, visit_time, conn, p_adj);
        }
    }
    node_list_[node].color_ = VisitColor::Black;
    visit_time += 1;
    node_list_[node].end_time_ = visit_time;
}

/*template<typename V>
void Graph<V>::DeEndDfsVisit(std::vector<std::vector<int> >& matrix, int node, std::vector<int>& strong_conn){
    visit_info_[node].color = VisitColor::Grey;
    for(int i = 0; i < matrix[node].size(); ++i){
        if(matrix[node][i] != NoEdge &&
           visit_info_[i].color == VisitColor::White){
               strong_conn.push_back(i);
               DeEndDfsVisit(matrix, i, strong_conn);
        }
    }
    visit_info_[node].color = VisitColor::Black;
}*/

template<typename V>
std::vector<std::vector<int> > Graph<V>::StrongConn(){
    Dfs();

    // transpose adjacency table
    int node_size = node_list_.size();
    Adj<std::tuple<int, int> > t_adj(node_size);
    for(int vertex1 = 0; vertex1 < node_size; ++vertex1){
        for(auto e = adj_[vertex1].begin(); e != adj_[vertex1].end(); e++){
            int vertex2 = std::get<0>(*e);
            int weight = std::get<1>(*e);
            t_adj[vertex2].push_back(std::make_tuple(vertex1, weight));
        }
    }

    //ShowDebugInfo();

    std::vector<std::vector<int> > res;
    std::vector<std::tuple<int, int> > visit_order;
    for(int i = 0; i < node_size; ++i)
        visit_order.push_back(std::make_tuple(i, node_list_[i].end_time_));
    sort(visit_order.begin(), visit_order.end(), [](std::tuple<int, int> a, std::tuple<int, int> b) -> bool {return std::get<1>(a) > std::get<1>(b);});
    // start Dfs on t_adj
    ColorReset(); VisitReset();
    int visit_time = 0;
    int conn_size = 0;
    for(int i = 0; i < visit_order.size(); ++i){
        int node = std::get<0>(visit_order[i]);
        if(node_list_[node].color_ == VisitColor::White){
            //std::cout << "Visit Node: " << node << std::endl;
            std::vector<int> slice;
            DfsVisit(node, visit_time, slice, &t_adj);
            res.push_back(slice);
        }
    }
    return res;
}

template<typename V>
std::vector<std::vector<int> > Graph<V>::Dfs(){
    ColorReset(); VisitReset();
    std::vector<std::vector<int> > conn;
    int visit_time = 0;
    for(int i = 0; i < node_list_.size(); ++i){
        if(node_list_[i].color_ == VisitColor::White){
            std::vector<int> slice;
            DfsVisit(i, visit_time, slice);
            conn.push_back(slice);
        }
    }
    return conn;
}

template<typename V>
void Graph<V>::ShowGraphInfo(){
    std::size_t vertex_num = adj_.size();

    std::cout << ' ' << '\t';
    for(unsigned i = 0; i < vertex_num; ++i)
        std::cout << i << '\t';
    std::cerr << std::endl;

    for(unsigned i = 0; i < vertex_num; ++i){
        std::cout << i << '\t';
        for(unsigned j = 0; j < vertex_num; ++j){
            int* edge_weight = findEdge(i, j);
            if(!edge_weight)
                std::cout << "--\t";
            else
                std::cout << *edge_weight << '\t';
        }
        std::cout << std::endl;
    }
}

template<typename V>
void Graph<V>::ShowVisitInfo(){
    std::size_t vertex_num = adj_.size();
    for(unsigned i = 0; i < vertex_num; ++i){
        std::cout << "vertex: " << i << '\t';
        std::cout << "start time: " << node_list_[i].start_time_ << '\t';
        std::cout << "end time: " << node_list_[i].end_time_ << '\t';
        std::cout << "visit color: ";
        switch(node_list_[i].color_){
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

template<typename V>
void Graph<V>::ShowDebugInfo(){
    std::size_t vertex_num = adj_.size();
    std::cout << "Graph vertex size: " << vertex_num << std::endl;

    std::cout << "Graph basic info:" << std::endl;
    ShowGraphInfo();

    std::cout << "Graph visit info:" << std::endl;
    ShowVisitInfo();
}

template<typename V>
void Graph<V>::GraphvizView(std::string filename, bool dump_png, bool dump_svg){
    // generate filename.gv
    std::ofstream graphfile(filename + std::string(".gv"));
    if(!graphfile.is_open()){
        std::cout << "Can't create graph file\n";
        exit(2);
    }
    graphfile << "digraph G {" << std::endl;
    for(int vertex1 = 0; vertex1 < adj_.size(); ++vertex1){
        for(auto e = adj_[vertex1].begin(); e != adj_[vertex1].end(); ++e){
            int vertex2 = std::get<0>(*e);
            graphfile << '\t' << std::to_string(vertex1) << " -> "
                      << std::to_string(vertex2) << ';' << std::endl;
        }
    }
    graphfile << '}';
    graphfile.close();
    std::string rm_gv_cmd = "rm " + filename + ".gv";
    if(dump_png){
        std::string dump_png_cmd = "dot -Tpng " + filename + ".gv -o " + filename +".png";
        system(dump_png_cmd.c_str());
    }
    if(dump_svg){
        std::string dump_svg_cmd = "dot -Tsvg " + filename + ".gv -o " + filename +".svg";
        system(dump_svg_cmd.c_str());
    }
    //system(rm_gv_cmd.c_str());
}

} // namespace graph

#endif