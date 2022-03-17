#include "Elements.hpp"

Edge::Edge(Vertex* from, Vertex* to, int cost, EdgeID edge_id){
    this->from = from;
    this->to = to;
    this->cost = cost;
    this->edge_id = edge_id;
}

EdgeID Edge::get_id(){
    EdgeID id = this->edge_id;
    return id;
}

VertexID Edge::get_from(){
    VertexID return_id = this->from->get_id();
    return return_id;
}

VertexID Edge::get_to(){
    VertexID return_id = this->to->get_id();
    return return_id;
}

int Edge::get_cost(){
    return this->cost;
}

void Edge::set_cost(int new_cost){
    this->cost = new_cost;
}

Edge::~Edge(){}






Vertex::Vertex(VertexID vertex_id){
    this->vertex_id = vertex_id;
}

VertexID Vertex::get_id(){
    return this->vertex_id;
}

std::vector<Edge*> Vertex::get_outbound_edges(){
    return this->outbound_edges;
}

std::vector<Edge*> Vertex::get_inbound_edges(){
    return this->inbound_edges;
}

bool Vertex::add_edge(Edge* edge){
    bool successful = false;

    //check if edge exists

    if (edge->get_from() == this->vertex_id){
        this->outbound_edges.push_back(edge);
        successful = true;
    }
    if (edge->get_to() == this->vertex_id){
        this->inbound_edges.push_back(edge);
        successful = true;
    }
    return successful;
}
bool Vertex::add_outbound_edge(Edge* edge){
    bool successful = false;

    //check if edge exists

    if (edge->get_from() == this->vertex_id){
        this->outbound_edges.push_back(edge);
        successful = true;
    }
    return successful;
}
bool Vertex::add_inbound_edge(Edge* edge){
    bool successful = false;

    //check if edge exists

    if (edge->get_from() == this->vertex_id){
        this->inbound_edges.push_back(edge);
        successful = true;
    }
    return successful;
}

Vertex::~Vertex(){}