#include "domain/Graph.h"
#include "domain/Iterators.h"
#include "function/APSP.h"
#include <string>
#include <iostream>
#include <chrono>
#include <cassert>

using namespace std::chrono;

#define clock high_resolution_clock::now

//void timeit(std::string output)

void graph1k_test(){
    auto start_time = clock();
    Graph graph1k = read_graph_from_file("./graph_input_test/graph1k.txt");
    //std::cout << graph.get_number_of_vertices() << " Vertices, " << graph.get_number_of_edges() << " Edges\n";
    
    auto stop_time = clock();
    std::cout << "Time to initialize the graph 1k: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();

    write_graph_to_file(graph1k, "./graph_output/original_graph.txt");

    stop_time = clock();

    std::cout << "Time to write graph1k to file: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
    start_time = clock();
    
    Graph new_copy = graph1k.copy();
    
    stop_time = clock();
    std::cout << "Time to copy graph1k: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
}

void graph_random_test(){
    auto start_time = clock();
    
    Graph random = create_random_graph_old(100000, 400000);
    //write_graph_to_file(new_copy, "./graph_output/copy_graph_test.txt");
    
    auto stop_time = clock();
    std::cout << "Time to create random graph (100k/400k): " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";

    start_time = clock();
    
    random.remove_vertex(0);
    
    stop_time = clock();
    std::cout << "Time to remove vertex 0: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";

    start_time = clock();
    
    //print_everything(new_copy);
    write_graph_to_file_inconsistent(random, "./graph_output/random_graph.txt");
    
    stop_time = clock();

    std::cout << "Time to write random to file: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
}

void random_input_test(){
    auto start_time = clock();
    
    Graph random = read_graph_from_file_inconsistent("./graph_output/random_graph.txt");
    //write_graph_to_file(new_copy, "./graph_output/copy_graph_test.txt");
    
    auto stop_time = clock();
    std::cout << "Time to read other format type: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
}

void graph100k_test(){
    auto start_time = clock();
    Graph graph100k = read_graph_from_file("./graph_input_test/graph100k.txt");
    
    auto stop_time = clock();
    std::cout << "Time to initialize the graph 100k: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
}

void graph1m_test(){
    auto start_time = clock();
    Graph graph1m = read_graph_from_file("./graph_input_test/graph1m.txt");
    
    auto stop_time = clock();
    std::cout << "Time to initialize the graph 1m: " << duration_cast<milliseconds>(stop_time - start_time).count() << "ms\n";
}

int main(){
    //run all stuff xdd
    // std::cout << "Running! \n";
    // graph1k_test();
    // graph100k_test();
    // graph1m_test();
    // graph_random_test();
    // random_input_test();
    
    /*{
        Matrix a = {{0,     3,   8, inf,  -4},
                {inf,   0, inf,   1,   7},
                {inf,   4,   0, inf, inf},
                {2,   inf,  -5,   0, inf},
                {inf, inf, inf,   6,   0}};
        Matrix identity(5, std::vector<int>(5, 0));
        for (int i = 0; i < 5; i++){
            identity[i][i] = 1;
        }
        Matrix final = APSP_starting_from(a, 0);
        print_matrix(final);
    }*/

    Graph temp = read_graph_from_file("./graph_input/matrix_manual1.txt");
    Matrix a = temp.get_matrix();
    Matrix final = APSP_starting_from(a, 0);
    print_matrix(final);
    //assert(temp.topo_sorted_vertices().empty());

    //temp.clear();
    //temp = read_graph_from_file("./graph_input/toposort-true.txt");

    //assert(!temp.topo_sorted_vertices().empty());

    std::cout << "\nDone!\n";

    return 0;
}