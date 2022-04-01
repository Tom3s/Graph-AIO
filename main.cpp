#include "./domain/Graph.hpp"
#include "./ui/UI.hpp"

int main(){
    Graph temp = read_graph_from_file("./graph_input_test/graph1k.txt");
    UI ui = UI(temp);

    while(ui.main_menu()){};

    //temp.clear();

    return 0;
}