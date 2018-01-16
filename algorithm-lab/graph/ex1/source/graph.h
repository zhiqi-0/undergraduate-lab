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
#include "heap.h"

#ifndef LZQ_GRAPH_H_
#define LZQ_GRAPH_H_

namespace graph{

template<typename E>
using Adj = std::vector<std::list<E> >;

template<typename T>
using TwoDArray = std::vector<std::vector<T> >;

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

    // basic operate
    std::vector<std::vector<int> > Dfs();
    std::tuple<bool, std::vector<int> > BellmanFord(int node);
    std::tuple<bool, std::vector<int> > Dijsktra(int node);
    std::tuple<TwoDArray<int>, std::vector<Adj<int> > > Johnson();
    std::vector<std::vector<int> > StrongConn();
    std::vector<std::list<int> > Path(int node);

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
        node_list_[i].start_time_ = node_list_[i].end_time_ = 0;
        node_list_[i].parent_ = i;
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

template<typename V>
std::vector<std::vector<int> > Graph<V>::Dfs(){
    ColorReset(); VisitReset();
    std::vector<std::vector<int> > conn;
    int visit_time = 0;
    for(int i = 0; i < node_list_.size(); ++i){
        if(node_list_[i].color_ == VisitColor::White){
            node_list_[i].parent_ = -1;
            std::vector<int> slice;
            DfsVisit(i, visit_time, slice);
            conn.push_back(slice);
        }
    }
    return conn;
}


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
            std::vector<int> slice;
            DfsVisit(node, visit_time, slice, &t_adj);
            res.push_back(slice);
        }
    }
    return res;
}

template<typename V>
std::tuple<bool, std::vector<int> > Graph<V>::BellmanFord(int node){
    int node_size = node_list_.size();
    VisitReset();
    std::vector<int> shortest_path(node_size, INT_MAX);
    shortest_path[node] = 0;
    for(int times = 0; times < node_size - 1; ++times){
        for(int u = 0; u < node_size; ++u){
            if(shortest_path[u] == INT_MAX) continue;
            for(auto e = adj_[u].begin(); e != adj_[u].end(); ++e){
                int v = std::get<0>(*e);
                int path_to_v = shortest_path[u] + std::get<1>(*e);       // v.d = u.d + e(u,v)
                if(path_to_v < shortest_path[v]){
                    shortest_path[v] = path_to_v;
                    node_list_[v].parent_ = u;
                }
            }
        }
    }
    for(int u = 0; u < node_size; ++u){
        if(shortest_path[u] == INT_MAX) continue;
        for(auto e = adj_[u].begin(); e != adj_[u].end(); ++e){
            int v = std::get<0>(*e);
            int weight = std::get<1>(*e);
            int path_to_v = shortest_path[u] + weight;       // v.d = u.d + e(u,v)
            if(path_to_v < shortest_path[v]){
                return std::make_tuple(false, shortest_path);
            }
        }
    }
    return std::make_tuple(true, shortest_path);
}

template<typename V>
std::tuple<bool, std::vector<int> > Graph<V>::Dijsktra(int node){
    int node_size = node_list_.size();
    VisitReset();
    struct VertexDis{
        int id;
        int d;
        VertexDis(int order, int distance = INT_MAX): id(order), d(distance) {}
        bool operator<(const VertexDis& rhs) {return d < rhs.d;}
        bool operator==(const VertexDis& rhs) {return id == rhs.id && d == rhs.d;}
        VertexDis& operator=(VertexDis& rhs) {id = rhs.id; d = rhs.d; return *this;}
    };

    std::vector<VertexDis> node_info;
    std::vector<int> shortest_path(node_size, INT_MAX);
    shortest_path[node] = 0;
    for(int i = 0; i < node_size; ++i){
        if(i != node)
            node_info.push_back(VertexDis(i));
        else
            node_info.push_back(VertexDis(node, 0));
    }
    
    heap::MinHeap<VertexDis> minheap(node_info);
    while(minheap.getHeapSize()){
        auto u = minheap.ExtractMin();
        if(u.d == INT_MAX) break;
        for(auto e = adj_[u.id].begin(); e != adj_[u.id].end(); ++e){
            int v = std::get<0>(*e);
            if(std::get<1>(*e) < 0)
                return std::make_tuple(false, shortest_path);
            int path_to_v = u.d + std::get<1>(*e);  // path_to_v = u.d + e(u, v)
            
            if(path_to_v < shortest_path[v]){
                //std::cout << v << ':' << u.id << std::endl;
                minheap.ResetKey(VertexDis(v, shortest_path[v]), VertexDis(v,path_to_v));
                shortest_path[v] = path_to_v;
                node_list_[v].parent_ = u.id;
            }
        }
    }
    return std::make_tuple(true, shortest_path);
}

template<typename V>
std::vector<std::list<int> > Graph<V>::Path(int node){
    //for(auto e : node_list_)
      //  std::cout << e.parent_ << "\t";
    int node_size = node_list_.size();
    std::vector<std::list<int> > path;
    for(int u = 0; u < node_list_.size(); ++u){
        //std::cout << "cal: " << u << std::endl;
        int p = node_list_[u].parent_;
        std::list<int> u_path;
        while(node_list_[p].parent_ != p){
            u_path.push_front(p);
            p = node_list_[p].parent_;
        }
        u_path.push_front(p);
        u_path.push_back(u);
        path.push_back(u_path);
    }
    //std::cout << "ok\n";
    return path;
}

template<typename V>
std::tuple<TwoDArray<int>, std::vector<Adj<int> > > Graph<V>::Johnson(){
    // insert a new node s
    int node_size = node_list_.size();
    node_list_.push_back(Vertex<int>(node_size));
    ++node_size;
    std::list<std::tuple<int, int> > new_v;
    for(int i = 0; i < node_size - 1; ++i)
        new_v.push_back(std::make_tuple(i, 0));
    adj_.push_back(new_v);

    // BellmanFord alg
    auto bellman = BellmanFord(node_size - 1);
    if(std::get<0>(bellman) == false){
        std::cout << "exist negative circle.\n";
        exit(-1);
    }
    // reset weight
    auto bres = std::get<1>(bellman);
    for(int u = 0; u < node_size; ++u){
        for(auto e = adj_[u].begin(); e != adj_[u].end(); ++e){
            int v = std::get<0>(*e);
            std::get<1>(*e) = std::get<1>(*e) + bres[u] - bres[v];
        }
    }
    // run dijsktra for node_size times
    std::vector<std::vector<int> > res;
    std::vector<Adj<int> > all_path;
    for(int node = 0; node < node_size - 1; ++node){
        auto dij = Dijsktra(node);
        // get path
        auto path = Path(node);
        path.pop_back();
        all_path.push_back(path);
        std::get<1>(dij).pop_back();
        res.push_back(std::get<1>(dij));
    }
    // update node distance
    --node_size;
    for(int s = 0; s < node_size; ++s){
        for(int u = 0; u < node_size; ++u){
            res[s][u] += bres[u] - bres[s];
        }
    }
    // recover original graph
    node_list_.pop_back();
    adj_.pop_back();
    for(int u = 0; u < node_size; ++u){
        for(auto e = adj_[u].begin(); e != adj_[u].end(); ++e){
            int v = std::get<0>(*e);
            std::get<1>(*e) = std::get<1>(*e) + bres[v] - bres[u];
        }
    }

    return std::make_tuple(res, all_path);
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
                      << std::to_string(vertex2)
                      << " [label=\"" << std::to_string(std::get<1>(*e)) << "\"];\n";
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
    system(rm_gv_cmd.c_str());
}

} // namespace graph

#endif