#pragma once

#include "Elements.h"
//#include "../../../DSA/TrueBoolArray/TrueBool.h"
#include <map>

#include <vector>
#include <fstream>
#include <string>

#define inf 2147483644/2

typedef std::vector<std::vector<int>> Matrix;

class EdgeIterator;
class VertexIterator;
class OutboundEdgeIterator;
class InboundEdgeIterator;

const Vertex NULL_VERTEX = Vertex(NULL_ID);
const Edge NULL_EDGE = Edge(nullptr, nullptr, NULL_ID, NULL_ID);

class Graph{

    friend Graph read_graph_from_file_inconsistent(std::string input_file);
    friend class EdgeIterator;
    friend class VertexIterator;
    friend class InboundEdgeIterator;
    friend class OutboundEdgeIterator;

    private:
        //int highest_vertex_id;
        //int number_of_edges;
        //int number_of_vertices;
        std::vector<Vertex*> vertices;
        std::vector<Edge*> edges;

        //int get_highest_vertex_id();
        std::vector<Vertex*> get_vertices(); //delete later
        std::vector<Edge*> get_edges(); //delete later
        Vertex* find_vertex_by_id(VertexID vertex_id);
        Edge* find_edge_by_id(EdgeID edge_id);
        Vertex* delete_vertex_by_id(VertexID vertex_id);
        Edge* delete_edge_by_id(EdgeID edge_id);
        std::map<Vertex*, Edge*> BFS(Vertex* start);
        std::vector<Vertex*> topo_sorted_vertices();
        
    
    public:
    
    //Graph(int nr_vertices, int nr_edges, TrueBoolArray& vertex_ids);
    Graph();
    Graph(int nr_vertices, int nr_edges);
    Graph(int nr_vertices);
    Graph(const Graph& old_graph);
    Graph& operator=(const Graph& old_graph);

    //iterator
    int get_number_of_vertices();
    int get_number_of_edges();

    //is edge
    EdgeID is_edge(VertexID from, VertexID to);
    //in degree
    int inbound_degree(VertexID vertex_id);
    //out degree
    int outbound_degree(VertexID vertex_id);
    //get endpoints of edge
    Endpoints get_endpoints(EdgeID edge_id);

    //add edge
    void initialize_edge(VertexID from, VertexID to, int cost, EdgeID edge_id);
    //void initialize_vertex(VertexID vertex_id);
    EdgeID add_edge(VertexID from, VertexID to, int cost);
    //get edge cost
    int get_edge_cost(EdgeID edge_id);
    //edit edge cost
    bool edit_edge_cost(EdgeID edge_id, int new_cost);
    //remove edge
    bool remove_edge(EdgeID edge_id);

    //add vertex
    VertexID add_vertex();
    //remove vertex
    bool remove_vertex(VertexID vertex_id);
    //vertex iterator
    VertexIterator vertex_iterator();

    int reverse_vertex_lookup(VertexID vertex_id);

    EdgeIterator edge_iterator();
    //inbound iterator
    InboundEdgeIterator inbound_edge_iterator(VertexID vertex_id);
    //outbound iterator
    OutboundEdgeIterator outbound_edge_iterator(VertexID vertex_id);

    bool verify_vertex(VertexID id);

    Matrix get_matrix();

    //copy graph
    Graph copy();

    //breadth-first search
    void print_bfs_path(VertexID from, VertexID to);

    std::vector<Graph> connected_components();

    std::vector<VertexID> longest_path(VertexID from, VertexID to);

    void clear();


    ~Graph();

};

Graph read_graph_from_file(std::string input_file);
void write_graph_to_file(Graph& graph, std::string output_file);
Graph read_graph_from_file_inconsistent(std::string input_file);
void write_graph_to_file_inconsistent(Graph& graph, std::string output_file);
Graph create_random_graph(int nr_vertices, int nr_edges);
Graph create_random_graph_old(int nr_vertices, int nr_edges);
void print_everything(Graph& graph);
