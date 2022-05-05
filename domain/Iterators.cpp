#include "Iterators.h"
#include <exception>


VertexIterator::VertexIterator(Graph& graph){
    this->list = graph.get_vertices();
    this->current = 0;
}

void VertexIterator::first(){
    this->current = 0;
}
void VertexIterator::next(){
    if (this->valid()){
        this->current++;
    } else {
        //error
    }
}

VertexID VertexIterator::get_current_vertex_id(){
    if (this->valid()){
        return this->list[this->current]->get_id();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

std::vector<Edge> VertexIterator::get_inbound_edges(){
    std::vector<Edge> return_vector;
    std::vector<Edge*> inbound_edges = this->list[this->current]->get_inbound_edges();
    for (int i = 0; i < inbound_edges.size(); i++){
        return_vector.push_back(*inbound_edges[i]);
    }
    return return_vector;
}

std::vector<Edge> VertexIterator::get_outbound_edges(){
    std::vector<Edge> return_vector;
    std::vector<Edge*> outbound_edges = this->list[this->current]->get_outbound_edges();
    for (int i = 0; i < outbound_edges.size(); i++){
        return_vector.push_back(*outbound_edges[i]);
    }
    return return_vector;
}

bool VertexIterator::valid(){
    if (this->current < this->list.size()){
        return true;
    }
    return false;
}

EdgeIterator::EdgeIterator(Graph& graph){
    this->list = graph.get_edges();
    this->current = 0;
}

void EdgeIterator::first(){
    this->current = 0;
}

void EdgeIterator::next(){
    if (this->valid()){
        this->current++;
    } else {
        //error
    }
}

EdgeID EdgeIterator::get_current_edge_id(){
    if (this->valid()){
        return this->list[this->current]->get_id();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

int EdgeIterator::get_current_edge_cost(){
    if (this->valid()){
        return this->list[this->current]->get_cost();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

EdgeID EdgeIterator::get_base_vertex(){
    if (this->valid()){
        return this->list[this->current]->get_from();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

EdgeID EdgeIterator::get_target_vertex(){
    if (this->valid()){
        return this->list[this->current]->get_to();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

bool EdgeIterator::valid(){
    if (this->current < this->list.size()){
        return true;
    }
    return false;
}




InboundEdgeIterator::InboundEdgeIterator(Graph& graph, VertexID vertex_id){
    Vertex* vertex = graph.find_vertex_by_id(vertex_id);
    if (vertex == nullptr) throw std::domain_error("Vertex not found when creating InboundEdgeIterator");
    this->list = vertex->get_inbound_edges();
    this->current = 0;
}

void InboundEdgeIterator::first(){
    this->current = 0;
}

void InboundEdgeIterator::next(){
    this->current++;
}

EdgeID InboundEdgeIterator::get_current_edge_id(){
    if (this->valid()){
        return this->list[this->current]->get_id();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

int InboundEdgeIterator::get_current_edge_cost(){
    if (this->valid()){
        return this->list[this->current]->get_cost();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

VertexID InboundEdgeIterator::get_current_base_vertex_id(){
    if (this->valid()){
        return this->list[this->current]->get_from();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

bool InboundEdgeIterator::valid(){
    if (this->current < this->list.size()){
        return true;
    }
    return false;
}


OutboundEdgeIterator::OutboundEdgeIterator(Graph& graph, VertexID vertex_id){
    Vertex* vertex = graph.find_vertex_by_id(vertex_id);
    if (vertex == nullptr) throw std::domain_error("Vertex not found when creating OutboundEdgeIterator");
    this->list = vertex->get_outbound_edges();
    this->current = 0;
}

void OutboundEdgeIterator::first(){
    this->current = 0;
}

void OutboundEdgeIterator::next(){
    this->current++;
}

EdgeID OutboundEdgeIterator::get_current_edge_id(){
    if (this->valid()){
        return this->list[this->current]->get_id();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

int OutboundEdgeIterator::get_current_edge_cost(){
    if (this->valid()){
        return this->list[this->current]->get_cost();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

VertexID OutboundEdgeIterator::get_current_target_vertex_id(){
    if (this->valid()){
        return this->list[this->current]->get_to();
    } else {
        throw std::exception();
        return NULL_ID;
        //error
    }
}

bool OutboundEdgeIterator::valid(){
    if (this->current < this->list.size()){
        return true;
    }
    return false;
}