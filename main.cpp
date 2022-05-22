#include "./domain/Graph.h"
#include "./ui/UI.h"
#include "./function/APSP.h"

// PW 3
// Write a program that, given a graph with costs and two vertices, finds a lowest cost walk between the given vertices,
// or prints a message if there are negative cost cycles accessible from the starting vertex. 
// The program will use a matrix defined as d[x,k]=the cost of the lowest cost walk from s to x 
// and of length at most k, where s is the starting vertex.

// PW 4
// Write a program that, given a graph with costs, does the following:
//  - verify if the corresponding graph is a DAG and performs a topological sorting of the activities using the algorithm based on predecessor counters;
//  - if it is a DAG, finds a highest cost path between two given vertices, in O(m+n).

int main(){
    Graph temp = read_graph_from_file("./graph_input/6_9.txt");

    std::cout << temp.get_number_of_edges() << "\n";
    //temp.print_bfs_path(10, 100);
    // int a;
    // Matrix m = temp.get_matrix();
    // // print_matrix(m);

    // Matrix distances;
    // try {
    //     distances = APSP_starting_from(m, 1);
    //     std::cout << "\n";
    //     print_matrix(distances);
    // } catch (const std::exception& ex) {
    //     std::cout << ex.what() << "\n";
    // }

    

    UI ui = UI(temp);

    while(ui.main_menu()){};

    //temp.clear();

    return 0;
}
// 10 <- 393 <- 714 <- 78 <- 114 <- 624 <- 100