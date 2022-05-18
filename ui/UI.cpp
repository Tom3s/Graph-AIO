#include "UI.h"
#include "../domain/Graph.h"
#include "../domain/Elements.h"
#include "../domain/Iterators.h"
#include "../function/APSP.h"

#include <iostream>

int convert_to_int(std::string string){
    int len = string.size();
    if (len > 9 || len == 0) return -1;
    int quantity = 0;
    int power = 1;
    for (int i = len - 1; i >= 0; i--){
        if (string[i] > '9' || string[i] < '0') return -1;
        quantity += power * (string[i] - '0');
        power *= 10;
    }
    return quantity;
}

UI::UI(Graph& _graph) : graph{ _graph }{
    //this->graph = graph;
    this->main_menu_options.push_back("Display properties of the graph");
    this->main_menu_options.push_back("Vertex menu");
    this->main_menu_options.push_back("Edge menu");
    this->main_menu_options.push_back("Get conncted components (written to files)");
    this->main_menu_options.push_back("Get shortest path cost");
    this->main_menu_options.push_back("Save to file");
    this->main_menu_options.push_back("Load graph from file (initial format)");
    this->main_menu_options.push_back("Load graph from file (format saved by the app)");
    this->main_menu_options.push_back("Generate random graph");
    this->main_menu_options.push_back("Exit");

    this->vertex_menu_options.push_back("Display one vertex");
    this->vertex_menu_options.push_back("Add new vertex");
    this->vertex_menu_options.push_back("Remove vertex");
    this->vertex_menu_options.push_back("Get inbound degree of a vertex");
    this->vertex_menu_options.push_back("Get outbound degree of a vertex");
    this->vertex_menu_options.push_back("Vertex iterator");
    this->vertex_menu_options.push_back("Back");

    this->edge_menu_options.push_back("Display one edge");
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

void UI::display_vertex(){
    VertexID this_vert;
    std::cout << "Enter vertex id: ";
    std::cin >> this_vert;

    if (!this->graph.verify_vertex(this_vert)){
        std::cout << "There is no vertex with id " << this_vert << "\n";
        return;
    }


    {
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
    }
}

void UI::add_vertex(){
    std::cout << "ID of the new vertex: " << this->graph.add_vertex() << std::endl;
}

void UI::remove_vertex(){
    std::string str;
    std::cout << "ID of vertex to remove:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    int input = convert_to_int(str);
    if (input == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    if (this->graph.remove_vertex(input)){
        std::cout << "Vertex " << input << " removed successfully!" << std::endl;
    } else {
        std::cout << "Vertex " << input << " is not part of the graph!" << std::endl;
    }
}

void UI::get_in_degree(){
    std::string str;
    std::cout << "ID of vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    int input = convert_to_int(str);
    if (input == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    int indegree = this->graph.inbound_degree(input);
    if (indegree == -1) {
        std::cout << "Vertex " << input << " is not part of the graph!" << std::endl;
        return;
    }

    std::cout << "Inbound degree of vertex " << input << " " << this->graph.inbound_degree(input) << std::endl;
}

void UI::get_out_degree(){
    std::string str;
    std::cout << "ID of vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    int input = convert_to_int(str);
    if (input == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    int outdegree = this->graph.inbound_degree(input);
    if (outdegree == -1) {
        std::cout << "Vertex " << input << " is not part of the graph!" << std::endl;
        return;
    }

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
        std::string str;
        std::cin >> str;
        int input = convert_to_int(str);

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
    std::string str;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    int input = convert_to_int(str);

    switch(input){
        case 1:
            this->display_vertex();
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
    std::string str;
    int from, to, cost;
    std::cout << "ID of base vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    from = convert_to_int(str);
    if (from == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cout << "ID of target vertex:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    to = convert_to_int(str);
    if (to == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cout << "Cost of edge:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    cost = convert_to_int(str);
    if (cost == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    EdgeID id = this->graph.add_edge(from, to, cost);

    if (id == NULL_ID){
        std::cout << "Error while adding edge!" << std::endl;
        return;
    }
    std::cout << "ID of new edge: " << id << std::endl;
}

void UI::remove_edge(){
    std::string str;
    std::cout << "ID of edge to remove:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    int input = convert_to_int(str);
    if (input == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    if (this->graph.remove_edge(input)){
        std::cout << "Edge " << input << " removed successfully!" << std::endl;
    } else {
        std::cout << "Edge " << input << " is not part of the graph!" << std::endl;
    }
}

void UI::edit_edge_cost(){
    int index, new_cost;
    std::string str;
    std::cout << "ID of edge to edit:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    index = convert_to_int(str);
    if (index == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cout << "New cost:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    new_cost = convert_to_int(str);
    if (new_cost == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    if (this->graph.edit_edge_cost(index, new_cost)){
        std::cout << "Edge updated successfully!" << std::endl;
    } else {
        std::cout << "Edge not found!" << std::endl;
    }
}

void UI::get_edge_properties(){
    int index;
    std::string str;
    std::cout << "ID of edge to get properties:" << std::endl;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    index = convert_to_int(str);
    if (index == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    int cost = this->graph.get_edge_cost(index);

    if (cost == -1){
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
    std::string str;
    std::cout << "Base vertex: " << std::endl << ">>> " << std::flush;
    std::cin >> str;
    base = convert_to_int(str);
    if (base == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cout << "Target vertex: " << std::endl << ">>> " << std::flush;
    std::cin >> str;
    target = convert_to_int(str);
    if (target == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

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
        std::string str;
        std::cin >> str;
        int input = convert_to_int(str);

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
    std::string str;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    int input = convert_to_int(str);

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

void UI::get_shortest_path_cost(){
    std::cout << "Get path costs from vertex: ";
    VertexID id;
    std::cin >> id;
    if (!this->graph.verify_vertex(id)){
        std::cout << "There is no vertex with id " << id << "\n";
        return;
    }

    Matrix adjecency = this->graph.get_matrix();

    
    Matrix costs;
    try {
        costs = APSP_starting_from(adjecency, id);
        //print_matrix(costs);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
        return;
    }

    int nr_steps;

    std::cout << "Target vertex: ";
    VertexID target;
    std::cin >> target;
    if (!this->graph.verify_vertex(target)){
        std::cout << "There is no vertex with id " << target << "\n";
        return;
    }

    std::cout << "Maximum number of steps: ";
    std::cin >> nr_steps;

    if (nr_steps < 1 || nr_steps > this->graph.get_number_of_vertices() - 1){
        std::cout << "Length of walk must be between 1 and " << this->graph.get_number_of_vertices() - 1 << "\n";
        return;
    }

    auto vector_min = [](std::vector<int> v, int l){
        int minim = inf;
        for (int i = 0; i < l - 1; i++){
            minim = std::min(minim, v[i]);
        }
        return minim;
    };

    int cost_of_walk = vector_min(costs[this->graph.reverse_vertex_lookup(target)], nr_steps);

    if (cost_of_walk == inf){
        std::cout << "There is no walk from " << id << " to " << target << " in " << nr_steps << " steps.\n";
        return;
    }

    std::cout << "Least cost walk from " << id << " to " << target << " in at most " << nr_steps << " steps:\n";
    std::cout << cost_of_walk << "\n";
}

void UI::get_connected_components(){
    std::string initial = "./connected/graph_";
    initial += std::to_string(this->graph.get_number_of_vertices());
    initial += "v_";
    initial += std::to_string(this->graph.get_number_of_edges());
    initial += "e_";

    std::vector<Graph> connected = this->graph.connected_components();

    for (int i = 0; i < connected.size(); i++){
        std::string ofile = initial;
        ofile += std::to_string(i);
        ofile += ".txt";
        write_graph_to_file_inconsistent(connected[i], ofile);
    }

    std::cout << "Connected components saved to files " << initial << "0-" << connected.size() - 1 << ".txt" << std::endl;
}

void UI::save_to_file(){
    std::string name;
    std::cout << "File name: \n>>> "; 
    std::cin >> name;
    name += ".txt";
    write_graph_to_file_inconsistent(this->graph, "./graph_output/" + name);
}

void UI::load_from_file_initial(){
    std::string name;
    std::cout << "File name: \n>>> "; 
    std::cin >> name;
    name += ".txt";
    this->graph.clear();
    this->graph = read_graph_from_file("./graph_input/" + name);
}

void UI::load_from_file_saved(){
    std::string name;
    std::cout << "File name: \n>>> "; 
    std::cin >> name;
    name += ".txt";
    this->graph.clear();
    this->graph = read_graph_from_file_inconsistent("./graph_output/" + name);
}
void UI::random_graph(){
    int nr_vertices, nr_edges;
    std::string str;
    std::cout << "Number of vertices:\n>>> ";
    std::cin >> str;
    nr_vertices = convert_to_int(str);
    if (nr_vertices == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cout << "Number of edges:\n>>> ";
    std::cin >> str;
    nr_edges = convert_to_int(str);
    if (nr_edges == -1){
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    if (nr_vertices * nr_vertices < nr_edges){
        std::cout << "Number of edges is too high!" << std::endl;
        return;
    }

    this->graph.clear();
    this->graph = create_random_graph_old(nr_vertices, nr_edges);
}

bool UI::main_menu(){
    this->print_main_menu();
    std::string str;
    std::cout << ">>> " << std::flush;
    std::cin >> str;
    int input = convert_to_int(str);

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
            this->get_connected_components();
            break;
        case 5:
            this->get_shortest_path_cost();
            break;
        case 6:
            this->save_to_file();
            break;
        case 7:
            this->load_from_file_initial();
            break;
        case 8:
            this->load_from_file_saved();
            break;
        case 9:
            this->random_graph();
            break;
        case 10:
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