#pragma once

#include "Elements.hpp"
#include "Graph.hpp"

class VertexIterator{

    //friend class Vertex;
    friend class Graph;

    private:
        std::vector<Vertex*> list;
        int current;

    public:
    
    VertexIterator();

    VertexIterator(Graph& graph);

    void first();
    void next();
    VertexID get_current_vertex_id();
    std::vector<Edge> get_inbound_edges();
    std::vector<Edge> get_outbound_edges();
    bool valid();
};

class InboundEdgeIterator{

    //friend class Vertex;
    friend class Graph;

    private:
        std::vector<Edge*> list;
        int current;

    public:
    InboundEdgeIterator();

    InboundEdgeIterator(Graph& graph, VertexID vertex_id);

    void first();
    void next();
    EdgeID get_current_edge_id();
    int get_current_edge_cost();
    VertexID get_current_base_vertex_id();
    bool valid();
};

class OutboundEdgeIterator{

    //friend class Vertex;
    friend class Graph;

    private:
        std::vector<Edge*> list;
        int current;

    public:

    OutboundEdgeIterator();

    OutboundEdgeIterator(Graph& graph, VertexID vertex_id);


    void first();
    void next();
    EdgeID get_current_edge_id();
    int get_current_edge_cost();
    VertexID get_current_target_vertex_id();
    bool valid();
};