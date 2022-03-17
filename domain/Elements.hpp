#pragma once

#include <vector>
//#include "Iterators.hpp"

//#define EdgeID int
//#define VertexID int
//#define Endpoints std::pair<EdgeID, EdgeID>
typedef int EdgeID;
typedef int VertexID;
typedef std::pair<EdgeID, EdgeID> Endpoints;

#define NULL_ID -12345


class Edge;
class Vertex;

class Edge{

    //friend class VertexIterator;
    friend class Graph;

    private:
        Vertex* from;
        Vertex* to;
        int cost;
        EdgeID edge_id;
    
    public:
    
    Edge(Vertex* from, Vertex* to, int cost, EdgeID edge_id);
    EdgeID get_id();
    VertexID get_from();
    VertexID get_to();
    int get_cost();
    void set_cost(int new_cost);
    ~Edge();
};


class Vertex{

    friend class VertexIterator;
    friend class InboundEdgeIterator;
    friend class OutboundEdgeIterator;
    friend class Graph;
    friend class Edge;

    private:
        std::vector<Edge*> inbound_edges;
        std::vector<Edge*> outbound_edges;
        VertexID vertex_id;

        std::vector<Edge*> get_inbound_edges();
        std::vector<Edge*> get_outbound_edges();
        bool remove_outbound_edge(Edge* edge);
        bool remove_inbound_edge(Edge* edge);

    public:

    Vertex(VertexID vertex_id);
    VertexID get_id();
    bool add_edge(Edge* edge);
    bool add_outbound_edge(Edge* edge);
    bool add_inbound_edge(Edge* edge);
    ~Vertex();
};