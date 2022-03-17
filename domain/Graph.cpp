#include "Graph.hpp"
#include "Iterators.hpp"
#include <string>
#include <fstream>

Graph::Graph(int nr_vertices, int nr_edges){
    //this->number_of_edges = nr_edges;
    //this->number_of_vertices = nr_vertices;
    this->vertices = std::vector<Vertex*>(nr_vertices, 0);
    this->edges = std::vector<Edge*>(nr_edges, 0);

    for (int i = 0; i < nr_vertices; i++){
        this->vertices[i] = new Vertex(i);
    }
}

std::vector<Vertex*> Graph::get_vertices(){
    return this->vertices;
}
std::vector<Edge*> Graph::get_edges(){
    return this->edges;
}


int Graph::get_number_of_vertices(){
    return this->vertices.size();
}
int Graph::get_number_of_edges(){
    return this->edges.size();
}

EdgeID Graph::is_edge(VertexID from, VertexID to){
    Vertex* vertex = this->find_vertex_by_id(from);
    std::vector<Edge*> outbound_edges = vertex->get_outbound_edges();

    for (int i = 0; i < outbound_edges.size(); i++){
        if (outbound_edges[i]->get_to() == to){
            return outbound_edges[i]->get_id();
        }
    }
    return NULL_ID;
}

int Graph::inbound_degree(VertexID vertex_id){
    Vertex* vertex = this->find_vertex_by_id(vertex_id);
    int degree = vertex->get_inbound_edges().size();
    return degree;
}
int Graph::outbound_degree(VertexID vertex_id){
    Vertex* vertex = this->find_vertex_by_id(vertex_id);
    int degree = vertex->get_outbound_edges().size();
    return degree;
}

Endpoints Graph::get_endpoints(EdgeID edge_id){
    Endpoints endpoints;
    Edge* edge = this->find_edge_by_id(edge_id);
    endpoints.first = edge->get_from();
    endpoints.second = edge->get_to();
    return endpoints;
}

Vertex* Graph::find_vertex_by_id(VertexID vertex_id){
    if (vertex_id > this->vertices[this->get_number_of_vertices() - 1]->get_id()){
        return nullptr;
    }

    int index = std::min(vertex_id, this->get_number_of_vertices() - 1);

    if (this->vertices[index]->get_id() == vertex_id){
        return this->vertices[index];
    }

    int middle = index / 2;
    VertexID current_id = this->vertices[middle]->get_id();
    while(current_id != vertex_id){
        if (current_id > vertex_id){
            middle /= 2;
        } else {
            middle = middle + middle / 2;
        }
        current_id = this->vertices[middle]->get_id();
    }
    return this->vertices[middle];
}
Vertex* Graph::delete_vertex_by_id(VertexID vertex_id){
    if (vertex_id > this->vertices[this->get_number_of_vertices() - 1]->get_id()){
        return nullptr;
    }

    int index = std::min(vertex_id, this->get_number_of_vertices() - 1);

    if (this->vertices[index]->get_id() == vertex_id){
        Vertex* return_pointer = this->vertices[index];
        this->vertices.erase(this->vertices.begin() + index);
        return return_pointer;
    }

    int middle = index / 2;
    VertexID current_id = this->vertices[middle]->get_id();
    while(current_id != vertex_id){
        if (current_id > vertex_id){
            middle /= 2;
        } else {
            middle = middle + middle / 2;
        }
        current_id = this->vertices[middle]->get_id();
    }
    Vertex* return_pointer = this->vertices[middle];
    this->vertices.erase(this->vertices.begin() + middle);
    return return_pointer;
}

Edge* Graph::find_edge_by_id(EdgeID edge_id){
    if (edge_id > this->edges[this->get_number_of_edges() - 1]->get_id()){
        return nullptr;
    }

    int index = std::min(edge_id, this->get_number_of_edges() - 1);

    if (this->edges[index]->get_id() == edge_id){
        return this->edges[index];
    }

    int middle = index / 2;
    VertexID current_id = this->edges[middle]->get_id();
    while(current_id != edge_id){
        if (current_id > edge_id){
            middle /= 2;
        } else {
            middle = middle + middle / 2;
        }
        current_id = this->edges[middle]->get_id();
    }
    return this->edges[middle];
}

Edge* Graph::delete_edge_by_id(EdgeID edge_id){
    if (edge_id > this->edges[this->get_number_of_edges() - 1]->get_id()){
        return nullptr;
    }

    int index = std::min(edge_id, this->get_number_of_edges() - 1);

    if (this->edges[index]->get_id() == edge_id){
        this->edges.erase(this->edges.begin() + index);
        return this->edges[index];
    }

    int middle = index / 2;
    VertexID current_id = this->edges[middle]->get_id();
    while(current_id != edge_id){
        if (current_id > edge_id){
            middle /= 2;
        } else {
            middle = middle + middle / 2;
        }
        current_id = this->edges[middle]->get_id();
    }

    this->edges.erase(this->edges.begin() + middle);
    return this->edges[middle];
}

void Graph::initialize_edge(VertexID from, VertexID to, int cost, EdgeID edge_id){
    Vertex* v_from = this->vertices[from];
    Vertex* v_to = this->vertices[to];


    Edge* new_edge = new Edge(v_from, v_to, cost, edge_id);
    
    v_from->add_outbound_edge(new_edge);
    v_to->add_inbound_edge(new_edge);

    this->edges[edge_id] = new_edge;
}

bool Graph::add_edge(VertexID from, VertexID to, int cost){
    Vertex* v_from = this->find_vertex_by_id(from);
    Vertex* v_to = this->find_vertex_by_id(to);

    if (v_from == nullptr || v_to == nullptr){
        return false;
    }

    Edge* new_edge = new Edge(v_from, v_to, cost, this->get_number_of_edges());

    this->edges.push_back(new_edge);

    //this->number_of_edges++;
    
    return true;
}

int Graph::get_edge_cost(EdgeID edge_id){
    Edge* edge = this->find_edge_by_id(edge_id);
    if (edge == nullptr){
        return NULL_ID;
    }
    return edge->get_cost();
}

bool Graph::edit_edge_cost(EdgeID edge_id, int new_cost){
    Edge* edge = this->find_edge_by_id(edge_id);
    if (edge == nullptr){
        return false;
    }
    edge->set_cost(new_cost);
    return true;
}

bool Graph::remove_edge(EdgeID edge_id){
    Edge* edge = this->delete_edge_by_id(edge_id);
    if (edge == nullptr){
        return false;
    }

    delete edge;
    return true;

}

VertexID Graph::add_vertex(){
    Vertex* vertex = new Vertex(this->get_number_of_vertices());
    this->vertices.push_back(vertex);
    return this->get_number_of_vertices() - 1;
}

bool Graph::remove_vertex(VertexID vertex_id){
    Vertex* vertex = this->delete_vertex_by_id(vertex_id);
    if (vertex == nullptr){
        return false;
    }

    std::vector<Edge*> inbound = vertex->get_inbound_edges();
    for (int i = inbound.size() - 1; i >= 0; i--){
        this->delete_edge_by_id(inbound[i]->get_id());
    }
    inbound.clear();

    std::vector<Edge*> outbound = vertex->get_outbound_edges();
    for (int i = outbound.size() - 1; i >= 0; i--){
        this->delete_edge_by_id(outbound[i]->get_id());
    }
    outbound.clear();

    delete vertex;
    return true;
}

VertexIterator Graph::vertex_iterator(){
    return VertexIterator(*this);
}

InboundEdgeIterator Graph::inbound_edge_iterator(VertexID vertex_id){
    return InboundEdgeIterator(*this, vertex_id);
}

OutboundEdgeIterator Graph::outbound_edge_iterator(VertexID vertex_id){
    return OutboundEdgeIterator(*this, vertex_id);
}

Graph::~Graph(){
    for (int i = 0; i < this->get_number_of_edges(); i++){
        delete this->edges[i];
    }

    for (int i = 0; i < this->get_number_of_vertices(); i++){
        delete this->vertices[i];
    }
}

Graph read_graph_from_file(std::string input_file){
    std::ifstream input_stream(input_file);
    int nr_vertices, nr_edges;
    input_stream >> nr_vertices >> nr_edges;
    int from, to, cost;

    Graph graph(nr_vertices, nr_edges);

    for (int i = 0; i < nr_edges; i++){
        input_stream >> from >> to >> cost;
        graph.initialize_edge(from, to, cost, i);
    }

    input_stream.close();

    return graph;
}

void write_graph_to_file(Graph graph, std::string output_file){
    std::ofstream ouput(output_file);
    ouput << graph.get_number_of_vertices() << " " << graph.get_number_of_edges() << "\n";
    VertexIterator iter = graph.vertex_iterator();
    
    while(iter.valid()){
        OutboundEdgeIterator targets = graph.outbound_edge_iterator(iter.get_current_vertex_id());
        while(targets.valid()){
            ouput << iter.get_current_vertex_id() << " " 
            << targets.get_current_target_vertex_id() << " " 
            << targets.get_current_edge_cost() << "\n";
            targets.next();
        }
        iter.next();
    }
    ouput.close();
}