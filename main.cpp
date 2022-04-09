#include "./domain/Graph.hpp"
#include "./ui/UI.hpp"

int main(){
    Graph temp = read_graph_from_file("./graph_input_test/connected_test.txt");
    //temp.print_bfs_path(10, 100);

    std::vector<Graph> connected = temp.connected_components();

    for (int i = 0; i < connected.size(); i++){
        std::string ofile = "connected";
        ofile += ('0' + i);
        ofile += ".txt";
        write_graph_to_file_inconsistent(connected[i], ofile);
    }

    UI ui = UI(temp);

    while(ui.main_menu()){};

    //temp.clear();

    return 0;
}
// 10 <- 393 <- 714 <- 78 <- 114 <- 624 <- 100