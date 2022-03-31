#include "./domain/Graph.hpp"
#include "./ui/UI.hpp"

int main(){
    //Graph temp = read_graph_from_file("./graph_input_test/graph_test.txt");
    Graph temp = create_random_graph(50, 150);
    // temp.remove_vertex(42);
    // print_everything(temp);
    // temp.remove_vertex(69);
    // print_everything(temp);
    // temp.remove_vertex(50);
    // print_everything(temp);
    UI ui = UI(temp);

    while(ui.main_menu()){};

    //temp.clear();

    return 0;
}