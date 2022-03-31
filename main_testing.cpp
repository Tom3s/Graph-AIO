#include "domain/Graph.hpp"
#include "domain/Iterators.hpp"
#include <string>
#include <iostream>
#include <chrono>

using namespace std::chrono;

#define clock high_resolution_clock::now

//void timeit(std::string output)


int main(){
    //run all stuff xdd
    std::cout << "Running! \n";


    auto start_time = clock();
    Graph graph = read_graph_from_file("./graph_input_test/graph1k.txt");
    std::cout << graph.get_number_of_vertices() << " Vertices, " << graph.get_number_of_edges() << " Edges\n";
    
    auto stop_time = clock();
    //print_everything(graph);
    std::cout << "Time to initialize the graph: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();

    write_graph_to_file(graph, "./graph_output/original_graph.txt");

    stop_time = clock();

    std::cout << "Time to write to file: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();
    
    Graph new_copy = graph.copy();
    //write_graph_to_file(new_copy, "./graph_output/copy_graph_test.txt");
    
    stop_time = clock();
    std::cout << "Time to copy graph: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();
    
    Graph random = create_random_graph(1000, 4000);
    //write_graph_to_file(new_copy, "./graph_output/copy_graph_test.txt");
    
    stop_time = clock();
    std::cout << "Time to create random graph: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();
    
    random.clear();
    //write_graph_to_file(new_copy, "./graph_output/copy_graph_test.txt");
    
    stop_time = clock();
    std::cout << "Time to clear random graph: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    
    start_time = clock();
    
    new_copy.remove_vertex(0);
    
    stop_time = clock();
    std::cout << "Time to remove vertex: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    
    start_time = clock();
    
    //print_everything(new_copy);
    write_graph_to_file(new_copy, "./graph_output/copy_graph.txt");
    
    stop_time = clock();

    std::cout << "Time to write copy to file: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    
    start_time = clock();

    graph.clear();
    
    stop_time = clock();
    std::cout << "Time to free up memory: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();
    
    
    new_copy.clear();
    

    stop_time = clock();
    std::cout << "Time to free up memory for copied graph: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();

    Graph new_test = read_graph_from_file("./graph_output/copy_graph.txt");
    
    stop_time = clock();
    std::cout << "Time to read altered graph file: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();
    
    
    new_test.clear();
    

    stop_time = clock();
    std::cout << "Time to free up memory for altered graph: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";

    return 0;
}