#include "domain/Graph.hpp"
#include <string>
#include <iostream>

int main(){
    //run all stuff xdd
    Graph graph = read_graph_from_file("graph1k.txt");
    
    write_graph_to_file(graph, "graph1k_test.txt");
    return 0;
}