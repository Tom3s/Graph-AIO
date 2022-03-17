#include "domain/Graph.hpp"
#include "domain/Iterators.hpp"
#include <string>
#include <iostream>

int main(){
    //run all stuff xdd
    Graph graph = read_graph_from_file("graph_test.txt");
    //std::cout << graph.get_number_of_vertices() << " " << graph.get_number_of_edges() << "\n";
    

    write_graph_to_file(graph, "leak_test.txt");
    
    print_everything(graph);
    
    graph.clear();

    return 0;
}