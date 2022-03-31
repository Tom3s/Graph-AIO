#include "UI.hpp"
#include "../domain/Graph.hpp"
#include "../domain/Elements.hpp"
#include "../domain/Iterators.hpp"

#include <iostream>

UI::UI(Graph& graph){
    this->graph = graph;
    this->main_menu_options.push_back("Display properties of the graph");
    this->main_menu_options.push_back("Vertex menu");
    this->main_menu_options.push_back("Edge menu");
    this->main_menu_options.push_back("Save to file");
    this->main_menu_options.push_back("Generate random graph");
    this->main_menu_options.push_back("Exit");

    this->vertex_menu_options.push_back("Display all vertices");
    this->vertex_menu_options.push_back("Add new vertex");
    this->vertex_menu_options.push_back("Remove vertex");
    this->vertex_menu_options.push_back("Get inbound degree of a vertex");
    this->vertex_menu_options.push_back("Get outbound degree of a vertex");
    this->vertex_menu_options.push_back("Vertex iterator");
    this->vertex_menu_options.push_back("Back");

    this->edge_menu_options.push_back("Display all edges");
    this->edge_menu_options.push_back("Add new edge");
    this->edge_menu_options.push_back("Remove edge");
    this->edge_menu_options.push_back("Edit edge cost");
    this->edge_menu_options.push_back("Get properties of edge");
    this->edge_menu_options.push_back("Check if edge exists");
    this->edge_menu_options.push_back("Edge iterator");
    this->edge_menu_options.push_back("Back");
}

void UI::print_main_menu(){
    for (int i = 0; i < this->main_menu_options.size(); i++){
        std::cout << i + 1 << ". " << this->main_menu_options[i] << std::endl;
    } 
}

void UI::print_vertex_menu(){
    for (int i = 0; i < this->vertex_menu_options.size(); i++){
        std::cout << i + 1 << ". " << this->vertex_menu_options[i] << std::endl;
    } 
}

void UI::print_edge_menu(){
    for (int i = 0; i < this->edge_menu_options.size(); i++){
        std::cout << i + 1 << ". " << this->edge_menu_options[i] << std::endl;
    } 
}

void UI::get_properties_of_graph(){
    std::cout << "Number of vertices: " << this->graph.get_number_of_vertices() << std::endl;
    std::cout << "Number of edges: " << this->graph.get_number_of_edges() << std::endl;
}

void UI::display_vertices(){
    VertexIterator vert_iter = this->graph.vertex_iterator();
    vert_iter.first();

    while (vert_iter.valid()){
        VertexID this_vert = vert_iter.get_current_vertex_id();
        std::cout << this_vert << ": " << std::endl;
        InboundEdgeIterator in_iter = this->graph.inbound_edge_iterator(this_vert);
        in_iter.first();
        std::cout << " in: "<< std::flush;
        while (in_iter.valid()){
            std::cout << in_iter.get_current_base_vertex_id() << " "<< std::flush;
            in_iter.next();
        }
        std::cout << std::endl;
        
        OutboundEdgeIterator out_iter = this->graph.outbound_edge_iterator(this_vert);
        out_iter.first();
        std::cout << " out: ";
        while (out_iter.valid()){
            std::cout << out_iter.get_current_target_vertex_id() << " "<< std::flush;
            out_iter.next();
        }
        std::cout << std::endl;
        vert_iter.next();
    }
}

void UI::add_vertex(){
    std::cout << "ID of the new vertex: " << this->graph.add_vertex() << std::endl;
}

void UI::remove_vertex(){
    int input;
    std::cout << "ID of vertex to remove:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> input;

    if (this->graph.remove_vertex(input)){
        std::cout << "Vertex " << input << " removed successfully!" << std::endl;
    } else {
        std::cout << "Vertex " << input << " is not part of the graph!" << std::endl;
    }
}

void UI::get_in_degree(){
    int input;
    std::cout << "ID of vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> input;

    std::cout << "Inbound degree of vertex " << input << " " << this->graph.inbound_degree(input) << std::endl;
}

void UI::get_out_degree(){
    int input;
    std::cout << "ID of vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> input;

    std::cout << "Outbound degree of vertex " << input << " " << this->graph.outbound_degree(input) << std::endl;
}

void UI::iterate_vertices(){
    //std::cout << "TODO" << std::endl;
    VertexIterator iter = this->graph.vertex_iterator();

    while (iter.valid()){
        VertexID current = iter.get_current_vertex_id();
        std::cout << current << ": \n";
        std::cout << "Inbound degree: " << iter.get_inbound_edges().size() << std::endl;
        std::cout << "Outbound degree: " << iter.get_outbound_edges().size() << std::endl;
        std::cout << "1. Remove vertex" << std::endl;
        std::cout << "2. Display inbound edges" << std::endl;
        std::cout << "3. Display outbound edges" << std::endl;
        std::cout << "4. Next vertex" << std::endl;
        std::cout << "5. Back" << std::endl;
        std::cout << ">>> " << std::flush;
        int input;
        std::cin >> input;
        if (input == 1){
            VertexID next;
            iter.next();
            this->graph.remove_vertex(current);
            if (iter.valid()){
                next = iter.get_current_vertex_id();
            } else return;
            iter = this->graph.vertex_iterator();
            while (iter.valid() && iter.get_current_vertex_id() != next){
                iter.next();
            }
        } else if (input == 2){
            InboundEdgeIterator edge_iter = this->graph.inbound_edge_iterator(current);
            while (edge_iter.valid()){
                std::cout << "From: " << edge_iter.get_current_base_vertex_id() << ", cost: " << edge_iter.get_current_edge_cost() << " (id: " << edge_iter.get_current_edge_id() <<")\n";
                edge_iter.next();
            }
        } else if (input == 3){
            OutboundEdgeIterator edge_iter = this->graph.outbound_edge_iterator(current);
            while (edge_iter.valid()){
                std::cout << "To: " << edge_iter.get_current_target_vertex_id() << ", cost: " << edge_iter.get_current_edge_cost() << " (id: " << edge_iter.get_current_edge_id() <<")\n";
                edge_iter.next();
            }
        } else if (input == 4){
            iter.next();
        } else if (input == 5){
            return;
        } else {
            std::cout << "Invalid option!" << std::endl;
        }
    }
    return;
}

bool UI::vertex_menu(){
    this->print_vertex_menu();
    int input;
    std::cout << ">>> " << std::flush;
    std::cin >> input;

    switch(input){
        case 1:
            this->display_vertices();
            break;
        case 2:
            this->add_vertex();
            break;
        case 3:
            this->remove_vertex();
            break;
        case 4:
            this->get_in_degree();
            break;
        case 5:
            this->get_out_degree();
            break;
        case 6:
            this->iterate_vertices();
            break;
        case 7:
            return false;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
            break;
    }
    return true;
}

void UI::display_edges(){
    EdgeIterator edge_iter = this->graph.edge_iterator();
    while (edge_iter.valid()){
        std::cout << edge_iter.get_current_edge_id() << ": from " << edge_iter.get_base_vertex() << " to " << edge_iter.get_target_vertex() << " (cost: " << edge_iter.get_current_edge_cost() << ")" << std::endl;
        edge_iter.next();
    }
}

void UI::add_edge(){
    int from, to, cost;
    std::cout << "ID of base vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> from;
    std::cout << "ID of target vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> to;
    std::cout << "Cost of edge:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> cost;

    EdgeID id = this->graph.add_edge(from, to, cost);

    if (id == NULL_ID){
        std::cout << "Error while adding edge!" << std::endl;
        return;
    }
    std::cout << "ID of new edge: " << id << std::endl;
}

void UI::remove_edge(){
    int input;
    std::cout << "ID of edge to remove:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> input;

    if (this->graph.remove_edge(input)){
        std::cout << "Edge " << input << " removed successfully!" << std::endl;
    } else {
        std::cout << "Edge " << input << " is not part of the graph!" << std::endl;
    }
}

void UI::edit_edge_cost(){
    int index, new_cost;
    std::cout << "ID of edge to edit:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> index;
    std::cout << "New cost:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> new_cost;

    if (this->graph.edit_edge_cost(index, new_cost)){
        std::cout << "Edge updated successfully!" << std::endl;
    } else {
        std::cout << "Edge not found!" << std::endl;
    }
}

void UI::get_edge_properties(){
    int index;
    std::cout << "ID of edge to get properties:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> index;

    int cost = this->graph.get_edge_cost(index);

    if (cost == NULL_ID){
        std::cout << "Edge is not part of the graph!" << std::endl;
        return;
    }

    Endpoints vertices = this->graph.get_endpoints(index);
    std::cout << "Base: " << vertices.first << std::endl;
    std::cout << "Target: " << vertices.second << std::endl;
    std::cout << "Cost: " << cost << std::endl;

}

void UI::check_if_edge_exists(){
    int base, target;
    std::cout << "Base vertex: " << std::endl << ">>> " << std::flush;
    std::cin >> base;
    std::cout << "Target vertex: " << std::endl << ">>> " << std::flush;
    std::cin >> target;

    EdgeID edge_id = this->graph.is_edge(base, target);

    if (edge_id == NULL_ID){
        std::cout << "There in no edge from " << base << " to " << target << std::endl;
        return;
    }

    std::cout << "ID of the edge from " << base << " to " << target << " is " << edge_id << std::endl;
}

void UI::iterate_edges(){
    EdgeIterator iter = this->graph.edge_iterator();

    while (iter.valid()){
        EdgeID current = iter.get_current_edge_id();
        EdgeID next;
        std::cout << current << ": \n";
        std::cout << "From: " << iter.get_base_vertex() << std::endl;
        std::cout << "To: " << iter.get_target_vertex() << std::endl;
        std::cout << "Cost: " << iter.get_current_edge_cost() << std::endl;

        std::cout << "1. Remove edge" << std::endl;
        std::cout << "2. Next edge" << std::endl;
        std::cout << "3. Back" << std::endl;
        std::cout << ">>> " << std::flush;
        int input;
        std::cin >> input;

        switch (input){
            case 1:
                this->graph.remove_edge(current);
                iter.next();
                if (iter.valid()){
                    next = iter.get_current_edge_id();
                } else return;
                iter = this->graph.edge_iterator();
                while (iter.valid() && iter.get_current_edge_id() != next){
                    iter.next();
                }
                break;
            case 2:
                iter.next();
                break;
            case 3:
                return;
                break;
            default:
                std::cout << "Invalid option!" << std::endl;
        }
    }
    return;
}

bool UI::edge_menu(){
    this->print_edge_menu();
    int input;
    std::cout << ">>> " << std::flush;
    std::cin >> input;

    switch(input){
        case 1:
            this->display_edges();
            break;
        case 2:
            this->add_edge();
            break;
        case 3:
            this->remove_edge();
            break;
        case 4:
            this->edit_edge_cost();
            break;
        case 5:
            this->get_edge_properties();
            break;
        case 6:
            this->check_if_edge_exists();
            break;
        case 7:
            this->iterate_edges();
            break;
        case 8:
            return false;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
            break;
    }
    return true;
}

void UI::save_to_file(){
    std::string name;
    std::cout << "File name: \n>>> "; 
    std::cin >> name;
    name += ".txt";
    write_graph_to_file_inconsistent(this->graph, "./graph_output/" + name);
}

void UI::random_graph(){
    int nr_vertices, nr_edges;
    std::cout << "Number of vertices:\n>>> ";
    std::cin >> nr_vertices;
    std::cout << "Number of edges:\n>>> ";
    std::cin >> nr_edges;

    if (nr_vertices * nr_vertices < nr_edges){
        std::cout << "Number of edges is too high!" << std::endl;
        return;
    }

    this->graph.~Graph();
    this->graph = create_random_graph(nr_vertices, nr_edges);
}

bool UI::main_menu(){
    this->print_main_menu();
    int input;
    std::cout << ">>> " << std::flush;
    std::cin >> input;

    switch(input){
        case 1:
            this->get_properties_of_graph();
            break;
        case 2:
            while (this->vertex_menu()){};
            break;
        case 3:
            while (this->edge_menu()){};
            break;
        case 4:
            this->save_to_file();
            break;
        case 5:
            this->random_graph();
            break;
        case 6:
            return false;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
            break;
    }
    return true;
}

UI::~UI(){
    (void)0;
}