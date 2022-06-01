#include "Graph.h"
#include "Iterators.h"
#include "TrueBool.h"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <map>
#include <queue>

Graph::Graph(){    
    this->vertices = std::vector<Vertex*>();
    this->edges = std::vector<Edge*>();
}

Graph::Graph(int nr_vertices, int nr_edges){
    //this->number_of_edges = nr_edges;
    //this->number_of_vertices = nr_vertices;

    //this->highest_vertex_id = -1;
    
    this->vertices = std::vector<Vertex*>(nr_vertices, nullptr);
    this->edges = std::vector<Edge*>();

    for (int i = 0; i < nr_vertices; i++){
        this->vertices[i] = new Vertex(i);
    }
}

// Graph::Graph(int nr_vertices, int nr_edges, TrueBoolArray& vertex_ids){
//     //this->number_of_edges = nr_edges;
//     //this->number_of_vertices = nr_vertices;

//     //this->highest_vertex_id = -1;
    
//     this->vertices = std::vector<Vertex*>();
//     this->edges = std::vector<Edge*>();

//     for (int i = 0; i < vertex_ids.get_size(); i++){
//         if (vertex_ids.get(i)){
//             Vertex* new_vertex = new Vertex(i);
//             this->vertices.push_back(new_vertex);
//         }
//     }
//     if (this->vertices.size() == nr_vertices) return;
//     //std::cout << this->vertices.size() << " " <<  nr_vertices << std::endl;

//     //Create vertecis
//     int index = 0;
//     while (this->vertices.size() < nr_vertices){
//         Vertex* new_vertex = new Vertex(this->vertices[this->vertices.size() - 1]->get_id() + 1);
//         this->vertices.push_back(new_vertex);
//     }
// }

Graph::Graph(int nr_vertices){
    //this->number_of_edges = nr_edges;
    //this->number_of_vertices = 0;
    //this->highest_vertex_id = highest_vertex_id;

    this->vertices = std::vector<Vertex*>(nr_vertices, nullptr);
    this->edges = std::vector<Edge*>();
}

Graph::Graph(const Graph& old_graph){
    //int highest_vertex_id = old_graph.highest_vertex_id;
    //this->number_of_vertices = 0;
    int nr_vertices = old_graph.vertices.size();
    int nr_edges = old_graph.edges.size();
    this->vertices = std::vector<Vertex*>(nr_vertices, nullptr);
    this->edges = std::vector<Edge*>();

    for (int i = 0; i < nr_vertices; i++){
        this->vertices[i] = new Vertex(old_graph.vertices[i]->get_id());
    }

    for (int i = 0; i < nr_edges; i++){
        VertexID from = old_graph.edges[i]->get_from();
        VertexID to = old_graph.edges[i]->get_to();
        int cost = old_graph.edges[i]->get_cost();
        this->add_edge(from, to, cost);
    }
}

// int Graph::get_highest_vertex_id(){
//     return this->highest_vertex_id;
// }

Graph& Graph::operator=(const Graph& old_graph){
    //Graph new_graph = Graph();
    int nr_vertices = old_graph.vertices.size();
    int nr_edges = old_graph.edges.size();
    this->vertices = std::vector<Vertex*>(nr_vertices, nullptr);
    this->edges = std::vector<Edge*>();

    for (int i = 0; i < nr_vertices; i++){
        this->vertices[i] = new Vertex(old_graph.vertices[i]->get_id());
    }

    for (int i = 0; i < nr_edges; i++){
        VertexID from = old_graph.edges[i]->get_from();
        VertexID to = old_graph.edges[i]->get_to();
        int cost = old_graph.edges[i]->get_cost();
        this->add_edge(from, to, cost);
    }
    return *this;
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
    if (vertex == nullptr) return NULL_ID;
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
    if (vertex == nullptr) return -1;
    int degree = vertex->get_inbound_edges().size();
    return degree;
}
int Graph::outbound_degree(VertexID vertex_id){
    Vertex* vertex = this->find_vertex_by_id(vertex_id);
    if (vertex == nullptr) return -1;
    int degree = vertex->get_outbound_edges().size();
    return degree;
}

Endpoints Graph::get_endpoints(EdgeID edge_id){
    Endpoints endpoints;
    Edge* edge = this->find_edge_by_id(edge_id);
    if (edge == nullptr){
        endpoints.first = NULL_ID;
        endpoints.second = NULL_ID;
    }
    endpoints.first = edge->get_from();
    endpoints.second = edge->get_to();
    return endpoints;
}

Vertex* Graph::find_vertex_by_id(VertexID vertex_id){
    int nr = this->get_number_of_vertices();
    int last_id = this->vertices[nr - 1]->get_id();
    if (vertex_id > last_id){
        return nullptr;
    }

    int index = std::min(vertex_id, this->get_number_of_vertices() - 1);

    if (this->vertices[index]->get_id() == vertex_id){
        return this->vertices[index];
    }


    int left = 0, right = index;
    int middle = (left + right) / 2;
    VertexID current_id = this->vertices[middle]->get_id();
    while(current_id != vertex_id){
        if (left >= right) return nullptr;
        if (current_id < vertex_id){
            left = middle + 1;
        } else {
            right = middle - 1;
        }
        middle = (left + right) / 2;
        current_id = this->vertices[middle]->get_id();
    }
    return this->vertices[middle];
}
Vertex* Graph::delete_vertex_by_id(VertexID vertex_id){
    if (vertex_id > this->vertices[this->vertices.size() - 1]->get_id()){
        return nullptr;
    }

    int index = std::min(vertex_id, this->get_number_of_vertices() - 1);

    if (this->vertices[index]->get_id() == vertex_id){
        Vertex* return_pointer = this->vertices[index];
        this->vertices.erase(this->vertices.begin() + index);
        return return_pointer;
    }

    int left = 0, right = index;
    int middle = (left + right) / 2;
    VertexID current_id = this->vertices[middle]->get_id();
    while(current_id != vertex_id){
        if (left >= right) return nullptr;
        if (current_id < vertex_id){
            left = middle + 1;
        } else {
            right = middle - 1;
        }
        middle = (left + right) / 2;
        current_id = this->vertices[middle]->get_id();
    }
    Vertex* return_pointer = this->vertices[middle];
    

    this->vertices.erase(this->vertices.begin() + middle);
    // if (this->vertices[vertex_id] == nullptr) return nullptr;
    // delete this->vertices[vertex_id];
    //this->vertices[vertex_id] = nullptr;

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

    int left = 0, right = index;
    int middle = (left + right) / 2;
    EdgeID current_id = this->edges[middle]->get_id();
    while(current_id != edge_id){
        if (left >= right) return nullptr;
        if (current_id < edge_id){
            left = middle + 1;
        } else {
            right = middle - 1;
        }
        middle = (left + right) / 2;
        current_id = this->edges[middle]->get_id();
    }
    Edge* return_pointer = this->edges[middle];
    return return_pointer;
}

Edge* Graph::delete_edge_by_id(EdgeID edge_id){
    if (edge_id > this->edges[this->get_number_of_edges() - 1]->get_id()){
        return nullptr;
    }

    int index = std::min(edge_id, this->get_number_of_edges() - 1);

    if (this->edges[index]->get_id() == edge_id){
        Edge* edge_pointer = this->edges[index];
        this->edges.erase(this->edges.begin() + index);
        return edge_pointer;
    }

    int left = 0, right = index;
    int middle = (left + right) / 2;
    EdgeID current_id = this->edges[middle]->get_id();
    while(current_id != edge_id){
        if (left >= right) return nullptr;
        if (current_id < edge_id){
            left = middle + 1;
        } else {
            right = middle - 1;
        }
        middle = (left + right) / 2;
        current_id = this->edges[middle]->get_id();
    }
    Edge* return_pointer = this->edges[middle];
    this->edges.erase(this->edges.begin() + middle);
    return return_pointer;
}

std::map<Vertex*, Edge*> Graph::BFS(Vertex* start){
    std::map<Vertex*, Edge*> parents;
    std::queue<Vertex*> queue;
    queue.push(start);
    parents[start] = nullptr;
    Vertex* current_vertex = start;
    while(!queue.empty()){
        current_vertex = queue.front();
        queue.pop();
        for (int i = 0; i < current_vertex->outbound_edges.size(); i++){
            Vertex* current_target = current_vertex->outbound_edges[i]->to;
            if (parents.find(current_target) == parents.end()){
                queue.push(current_target);
                parents[current_target] = current_vertex->outbound_edges[i];
            }
        }
    }
    return parents;
}

void Graph::initialize_edge(VertexID from, VertexID to, int cost, EdgeID edge_id){
    Vertex* v_from = this->find_vertex_by_id(from);//this->vertices[from];
    Vertex* v_to = this->find_vertex_by_id(to);//this->vertices[to];

    Edge* new_edge = new Edge(v_from, v_to, cost, edge_id);
    
    v_from->add_outbound_edge(new_edge);
    v_to->add_inbound_edge(new_edge);

    this->edges.push_back(new_edge);

    //std::cout << "Nr. edges: " << this->get_number_of_edges() << "\n";
    //this->edges[edge_id] = new_edge;
}
// void Graph::initialize_vertex(VertexID vertex_id){
//     while (this->vertices.size() <= vertex_id){
//         this->vertices.push_back(nullptr);
//     }
//     this->highest_vertex_id = std::max(vertex_id, this->highest_vertex_id);
//     if (this->vertices[vertex_id] == nullptr){
//         this->vertices[vertex_id] = new Vertex(vertex_id);
//         //this->number_of_vertices++;
//     }
//     //std::cout << "Nr. edges: " << this->get_number_of_edges() << "\n";
//     //this->edges[edge_id] = new_edge;
// }

EdgeID Graph::add_edge(VertexID from, VertexID to, int cost){
    if (this->is_edge(from, to) != NULL_ID) return NULL_ID;
    
    Vertex* v_from = this->find_vertex_by_id(from);
    Vertex* v_to = this->find_vertex_by_id(to);

    if (v_from == nullptr || v_to == nullptr){
        return NULL_ID;
    }

    EdgeID edge_id;
    if (this->edges.size() == 0){
        edge_id = 0;
    } else {
        edge_id = this->edges[this->get_number_of_edges() - 1]->get_id() + 1;
    }
    Edge* new_edge = new Edge(v_from, v_to, cost, edge_id);

    v_from->add_outbound_edge(new_edge);
    v_to->add_inbound_edge(new_edge);

    this->edges.push_back(new_edge);

    //this->number_of_edges++;
    
    return new_edge->edge_id;
}

int Graph::get_edge_cost(EdgeID edge_id){
    Edge* edge = this->find_edge_by_id(edge_id);
    if (edge == nullptr){
        return -1;
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

    Vertex* from = edge->from;
    Vertex* to = edge->to;

    from->remove_outbound_edge(edge);
    to->remove_inbound_edge(edge);

    delete edge;
    return true;

}

VertexID Graph::add_vertex(){
    VertexID new_id = this->vertices[this->vertices.size() - 1]->get_id() + 1;
    Vertex* vertex = new Vertex(new_id);
    this->vertices.push_back(vertex);
    //this->highest_vertex_id = this->vertices.size();
    //this->number_of_vertices++;

    return new_id;
}

bool Graph::remove_vertex(VertexID vertex_id){
    Vertex* vertex = this->delete_vertex_by_id(vertex_id);
    if (vertex == nullptr){
        return false;
    }

    for (int i = this->get_number_of_edges() - 1; i >= 0; i--){
        Edge* current_edge = this->edges[i];
        if (current_edge->get_from() == vertex_id || current_edge->get_to() == vertex_id){
            current_edge->from->remove_outbound_edge(current_edge);
            //std::cout << i << ": 1\n";
            current_edge->to->remove_inbound_edge(current_edge);
            //std::cout << i << ": 2\n";
            this->edges.erase(this->edges.begin() + i);
            //std::cout << i << ": 3\n";
            //i--;
            //std::cout << i << ": 4\n";
            delete current_edge;
            //std::cout << i << ": 5\n";
        }
    }
    //this->number_of_vertices--;
    delete vertex;
    return true;
}

VertexIterator Graph::vertex_iterator(){
    return VertexIterator(*this);
}

EdgeIterator Graph::edge_iterator(){
    return EdgeIterator(*this);
}

InboundEdgeIterator Graph::inbound_edge_iterator(VertexID vertex_id){
    return InboundEdgeIterator(*this, vertex_id);
}

OutboundEdgeIterator Graph::outbound_edge_iterator(VertexID vertex_id){
    return OutboundEdgeIterator(*this, vertex_id);
}

void Graph::clear(){
    
    for (int i = this->get_number_of_edges() - 1 ; i >= 0; i--){
        delete this->edges[i];
    }
    
    for (int i = this->get_number_of_vertices() - 1; i >= 0; i--){
        delete this->vertices[i];
    }
}

Graph Graph::copy(){
    //int highest_vertex_id = this->get_highest_vertex_id();
    int nr_vertices = this->get_number_of_vertices();
    int nr_edges = this->get_number_of_edges();
    Graph new_graph = Graph(nr_vertices);
    //new_graph.number_of_vertices = this->get_number_of_vertices();
    for (int i = 0; i < nr_vertices; i++){
        new_graph.vertices[i] = new Vertex(this->vertices[i]->get_id());
    }

    for (int i = 0; i < nr_edges; i++){
        VertexID from = this->edges[i]->get_from();
        VertexID to = this->edges[i]->get_to();
        int cost = this->edges[i]->get_cost();
        EdgeID id = this->edges[i]->get_id();
        new_graph.initialize_edge(from, to, cost, id);
    }

    return new_graph;
}

void Graph::print_bfs_path(VertexID from, VertexID to){
    Vertex* start = find_vertex_by_id(from);
    Vertex* end = find_vertex_by_id(to);
    if (start == nullptr || end == nullptr){
        return;
    }

    std::map<Vertex*, Edge*> parents = this->BFS(start);

    std::vector<VertexID> path;

    Vertex* current = end;
    Edge* curr_edge;
    while (true){
        path.push_back(current->get_id());
        curr_edge = parents[current];
        if (curr_edge == nullptr) break;
        current = parents[current]->from;
    }
    std::reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++){
        std::cout << path[i] << " <- " << std::flush;
    }
}



std::vector<Graph> Graph::connected_components(){
    //create undurected graph
    Graph undirected = this->copy();
    // for (int i = 0; i < this->get_number_of_edges(); i++){
    //     undirected.add_edge(this->edges[i]->get_to(), this->edges[i]->get_from(), this->edges[i]->get_cost());
    // }

    EdgeIterator edge_iter = this->edge_iterator();

    while (edge_iter.valid()){
        if (edge_iter.get_base_vertex() == edge_iter.get_target_vertex()){
            undirected.remove_edge(edge_iter.get_current_edge_id());
            edge_iter.next();
            continue;
        }
        undirected.add_edge(edge_iter.get_target_vertex(), edge_iter.get_base_vertex(), edge_iter.get_current_edge_cost());
        edge_iter.next();
    }

    //std::cout << "Nr edges orig: " << this->get_number_of_edges() << " undirected edges: " << undirected.get_number_of_edges() << "\n";
    //write_graph_to_file_inconsistent(undirected, "./graph_output/undirected.txt");
    // the largiest VertexID is the last from the list
    VertexID largest_id = this->vertices[this->vertices.size() - 1]->get_id();
    // create bool array to keep track of visited vertices
    // false -> already used, true-> not yet visited
    TrueBoolArray used_vertices = TrueBoolArray(largest_id + 1, false);
    
    // only set true (visitable) the vertices that exist in the graph
    for (int i = 0; i < this->vertices.size(); i++){
        used_vertices.set(this->vertices[i]->get_id(), true);
    }
    std::vector<Graph> connected_graph_list;

    //loop trough all vertices
    for (int i = 0; i < used_vertices.get_size(); i++){
        if (!used_vertices.get(i)) continue; // skip to next if already visited

        // perform BFS on current vertex
        Vertex* current_vertex = this->find_vertex_by_id(i);
        std::map<Vertex*, Edge*> parents = undirected.BFS(current_vertex);

        // create bool array, that keeps track of which vertices are part of the current component
        TrueBoolArray connected_vertices = TrueBoolArray(largest_id + 1, false);

        Graph partial_graph(parents.size());
        //iterate through vertices
        int index = 0;
        for (const auto &pair : parents){
            //log if they've been used
            used_vertices.set(pair.first->vertex_id, false);
            connected_vertices.set(pair.first->vertex_id, true);
            //create graph with these vertices
            partial_graph.vertices[index] = new Vertex(pair.first->vertex_id);
            index++;
        }

        //sort vertices by ID
        std::sort(partial_graph.vertices.begin(), partial_graph.vertices.end(), [](Vertex* a, Vertex* b){ 
            return a->get_id() < b->get_id(); 
        });

        //add edges that contain only these vertices
        for (int j = 0; j < this->edges.size(); j++){
            Edge* edge_candidate = this->edges[j];
            if (connected_vertices.get(edge_candidate->get_from()) && connected_vertices.get(edge_candidate->get_to())){
                partial_graph.add_edge(edge_candidate->get_from(), edge_candidate->get_to(), edge_candidate->get_cost());
            }
        }
        //repeat until no vertex is left
        connected_graph_list.push_back(partial_graph);
    }

    return connected_graph_list;
}

bool Graph::verify_vertex(VertexID id){
    return this->find_vertex_by_id(id) != nullptr;
}

int Graph::reverse_vertex_lookup(VertexID vertex_id){
    int pos = std::min((unsigned long long)vertex_id, this->vertices.size() - 1);
    while (this->vertices[pos]->get_id() != vertex_id){
        pos--;
    }
    return pos;
}

Matrix Graph::get_matrix(){
    int n = this->vertices.size();

    Matrix m(n, std::vector<int>(n, inf));
    for (int i = 0; i < n; i++){
        m[i][i] = 0;
    }

    std::vector<VertexID> lookup(n, 0);
    for (int i = 0; i < n; i++){
        lookup[i] = this->vertices[i]->vertex_id;
    }

    for (Vertex* v : this->vertices){
        OutboundEdgeIterator iter = this->outbound_edge_iterator(v->vertex_id);
        while (iter.valid()){
            m[v->vertex_id][this->reverse_vertex_lookup(iter.get_current_target_vertex_id())] = iter.get_current_edge_cost();
            iter.next();
        }
    }

    return m;
}

std::vector<Vertex*> Graph::topo_sorted_vertices(){
// Input:
//     G : directed graph
// Output:
//     sorted : a list of vertices in topological sorting order, or null if G has cycles
// Algorithm:
//     sorted = emptyList
    std::vector<Vertex*> sorted_list;
//     Queue q
    std::queue<Vertex*> Q;
//     Dictionary count
    std::map<Vertex*, int> count;
//     for x in X do
    for (auto vertex : this->vertices){
    //         count[x] = indeg(x)
        count[vertex] = vertex->inbound_edges.size();
    //         if count[x] == 0 then
        if (count[vertex] == 0) {
    //             q.enqueue(x)
            Q.push(vertex);
    //         endif
        } 
//     endfor
    }
//     while not q.isEmpty() do
    Vertex* current;
    while (!Q.empty()){
//         x = q.dequeue()
        current = Q.front();
        Q.pop();
//         sorted.append(x)
        sorted_list.push_back(current);
//         for y in Nout(x) do
        for (auto out_edge : current->outbound_edges){
//             count[y] = count[y] - 1
            count[out_edge->to]--;
//             if count[y] == 0 then
            if (count[out_edge->to] == 0){
//                 q.enqueue(y)
                Q.push(out_edge->to);
//             endif
            }
//         endfor
        }
//     endwhile
    }
//     if sorted.size() < X.size() then
    if (sorted_list.size() < this->vertices.size()){
//         sorted = null
        return std::vector<Vertex*>();
//     endif
    }
    return sorted_list;
}

Graph::~Graph(){
    
    
    for (int i = this->get_number_of_edges() - 1 ; i >= 0; i--){
        delete this->edges[i];
    }
    //this->edges.clear();
    
    for (int i = this->get_number_of_vertices() - 1; i >= 0; i--){
        delete this->vertices[i];
    }
    //this->vertices.clear();
    
}

Graph read_graph_from_file(std::string input_file){
    std::ifstream input_stream(input_file);
    int nr_vertices, nr_edges;
    input_stream >> nr_vertices >> nr_edges;
    //TrueBoolArray vertex_ids = TrueBoolArray(nr_vertices + 1);
    int from, to, cost;

    Graph graph(nr_vertices, nr_edges);

    for (int i = 0; i < nr_edges; i++){
        input_stream >> from >> to >> cost;
        // graph.initialize_vertex(from);
        // graph.initialize_vertex(to);
        graph.initialize_edge(from, to, cost, i);
        // if (std::max(from, to) > nr_vertices){
        //     vertex_ids.resize(std::max(from, to) + 1);
        // }
        // vertex_ids.set(from, true);
        // vertex_ids.set(to, true);
    }
    //input_stream.close();

    //input_stream.open(input_file);
    // input_stream >> nr_vertices >> nr_edges;
    // Graph graph(nr_vertices, nr_edges, vertex_ids);

    // for (int i = 0; i < nr_edges; i++){
    //     input_stream >> from >> to >> cost;
    //     // graph.initialize_vertex(from);
    //     // graph.initialize_vertex(to);
    //     graph.add_edge(from, to, cost);
    // }

    return graph;
}

std::vector<VertexID> Graph::longest_path(VertexID from, VertexID to){
    std::vector<Vertex*> toposorted = this->topo_sorted_vertices();

    if (toposorted.size() == 0) {
        return std::vector<VertexID>();
    }

    int start_index = -1;
    int end_index = -1;

    for (int i = 0; i < toposorted.size(); i++){
        if (toposorted[i]->get_id() == to){
            end_index = i;
            break;
        }

        if (toposorted[i]->get_id() == from){
            start_index = i;
        }
    }
    if (start_index == -1){
        return std::vector<VertexID>();
    }

    std::map<Vertex*, Vertex*> parent_list;
    std::vector<int> costs = std::vector<int>(toposorted.size(), -1);

    costs[start_index] = 0;

    for (int i = start_index + 1; i <= end_index; i++){
        int max_score = INT_MIN, current_score;
        Edge* max_edge;
        for (int j = i - 1; j >= start_index; j--){
            //check if inside path bounds
            //calculate score
            EdgeID current = this->is_edge(toposorted[j]->get_id(), toposorted[i]->get_id());
            if (current != NULL_ID){
                current_score = costs[j] + this->get_edge_cost(current);
                if (current_score >= max_score){
                    max_score = current_score;
                    max_edge = this->find_edge_by_id(current);
                }
            }
            //save if better
        }
        costs[i] = max_score;
        parent_list[max_edge->to] = max_edge->from;
    }

    std::cout << "DEBUG: " << costs[end_index] << "\n";

    Vertex* path_builder = toposorted[end_index];

    std::vector<VertexID> path;

    path.push_back(path_builder->get_id());

    while (path_builder != this->find_vertex_by_id(from)){
        path.push_back(parent_list[path_builder]->get_id());
        path_builder = parent_list[path_builder];
    }

    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<VertexID> Graph::tsp_solver(int& cost, VertexID start_index){
    std::map<Vertex*, bool> used;

    int nr_used = 1;

    for (auto vert : this->vertices){
        used[vert] = false;
    }

    std::vector<VertexID> path;


    cost = 0;

    auto current_vertex = this->find_vertex_by_id(start_index);

    path.push_back(current_vertex->get_id());

    do {
        int min_cost = INT_MAX;
        Vertex* min_vert = nullptr;

        auto outbound = current_vertex->get_outbound_edges();

        for (auto edge : outbound){
            if (edge->get_cost() < min_cost && !used[edge->to]){
                if (edge->get_to() == path.front() && nr_used < this->get_number_of_vertices()) continue;
                min_cost = edge->get_cost();
                min_vert = edge->to;
            }
        }

        if (min_vert == nullptr){
            throw std::runtime_error("infinite loop");
        }

        used[min_vert] = true;
        path.push_back(min_vert->get_id());
        cost += min_cost;
        nr_used ++;
        
        current_vertex = min_vert;

    } while (current_vertex->get_id() != path.front());

    return path;
}

std::vector<VertexID> Graph::TSP(int& _cost){
    _cost = INT_MAX;
    std::vector<VertexID> best;

    auto iter = this->vertex_iterator();

    while (iter.valid()){
        int cost;
        std::vector<VertexID> path;
        try {
            path = this->tsp_solver(cost, iter.get_current_vertex_id());
        } catch (std::exception& ex){
            iter.next();
            continue;
        }

        if (cost < _cost){
            _cost = cost;
            best = path;
        }
        iter.next();

    }
    return best;
}


Graph read_graph_from_file_inconsistent(std::string input_file){
    std::ifstream input_stream(input_file);
    int nr_vertices, nr_edges;
    input_stream >> nr_vertices >> nr_edges;

    Graph graph(nr_vertices);
    int vertex;
    for (int i = 0; i < nr_vertices; i++){
        input_stream >> vertex;
        graph.vertices[i] = new Vertex(vertex);
    }

    int from, to, cost, id;
    for (int i = 0; i < nr_edges; i++){
        input_stream >> from >> to >> cost >> id;
        // graph.initialize_vertex(from);
        // graph.initialize_vertex(to);
        // graph.add_edge(from, to, cost);
        graph.initialize_edge(from, to, cost, id);
    }

    return graph;
}

void write_graph_to_file(Graph& graph, std::string output_file){
    std::ofstream ouput(output_file);
    ouput << graph.get_number_of_vertices() << " " << graph.get_number_of_edges() << "\n";
    EdgeIterator iter = graph.edge_iterator();
    
    while(iter.valid()){
        ouput << iter.get_base_vertex() << " " 
        << iter.get_target_vertex() << " " 
        << iter.get_current_edge_cost() << "\n";
        iter.next();
    }
    ouput.close();
}
void write_graph_to_file_inconsistent(Graph& graph, std::string output_file){
    std::ofstream ouput(output_file);
    ouput << graph.get_number_of_vertices() << " " << graph.get_number_of_edges() << "\n";
    VertexIterator vert = graph.vertex_iterator();
    while(vert.valid()){
        ouput << vert.get_current_vertex_id() << "\n";
        vert.next();
    }

    EdgeIterator iter = graph.edge_iterator();
    
    while(iter.valid()){
        ouput << iter.get_base_vertex() << " " 
        << iter.get_target_vertex() << " " 
        << iter.get_current_edge_cost() << " "
        << iter.get_current_edge_id() << "\n";
        iter.next();
    }
    ouput.close();
}

void print_everything(Graph& graph){
    EdgeIterator edge_iter = graph.edge_iterator();
    while (edge_iter.valid()){
        std::cout << edge_iter.get_base_vertex() << " " << edge_iter.get_target_vertex() << " " << edge_iter.get_current_edge_cost() << "\n";
        edge_iter.next();
    }
    std::cout << "\n";

    VertexIterator vert_iter = graph.vertex_iterator();
    vert_iter.first();

    while (vert_iter.valid()){
        VertexID this_vert = vert_iter.get_current_vertex_id();
        std::cout << this_vert << ": \n";
        InboundEdgeIterator in_iter = graph.inbound_edge_iterator(this_vert);
        in_iter.first();
        std::cout << " in: ";
        while (in_iter.valid()){
            std::cout << in_iter.get_current_base_vertex_id() << " ";
            in_iter.next();
        }
        std::cout << "\n";
        
        OutboundEdgeIterator out_iter = graph.outbound_edge_iterator(this_vert);
        out_iter.first();
        std::cout << " out: ";
        while (out_iter.valid()){
            std::cout << out_iter.get_current_target_vertex_id() << " ";
            out_iter.next();
        }
        std::cout << "\n";
        vert_iter.next();
    }
}

Graph create_random_graph(int nr_vertices, int nr_edges){
    Graph graph = Graph(nr_vertices, nr_edges);
    EdgeID id = 0;
    for (int i = 0; i < nr_vertices; i++){
        if (id >= nr_edges){
            break;
        }
        for (int j = 0; j < nr_vertices; j++){
            if (id >= nr_edges){
                break;
            }
            if (std::rand() % 2){
                int cost = std::rand() % 100;
                graph.initialize_edge(i, j, cost, id);
                //std::cerr << "Edge nr " << id << std::endl;
                id++;
            }
        }
        //std::cerr << "still looping" << std::endl;
    }

    int remaining_edges = nr_edges - id;


    for (int i = 0; i < remaining_edges; i++){
        int from = std::rand() % nr_vertices;
        int to = std::rand() % nr_vertices;
        int cost = std::rand() % 100;
        while (graph.is_edge(from, to) != NULL_ID){
            from = std::rand() % nr_vertices;
            to = std::rand() % nr_vertices;
        }
        graph.initialize_edge(from, to, cost, id);
        //std::cerr << "Edge nr " << id << std::endl;
        id++;
    }
    return graph;
}
Graph create_random_graph_old(int nr_vertices, int nr_edges){
    Graph graph = Graph(nr_vertices, nr_edges);
    for (int i = 0; i < nr_edges; i++){
        int from = std::rand() % nr_vertices;
        int to = std::rand() % nr_vertices;
        int cost = std::rand() % 100;
        while (graph.is_edge(from, to) != NULL_ID){
            from = std::rand() % nr_vertices;
            to = std::rand() % nr_vertices;
        }
        graph.initialize_edge(from, to, cost, i);
        //std::cerr << "Edge nr " << i << std::endl;
    }
    return graph;
}