#include "../domain/Graph.hpp"

class UI{
    private:
        Graph graph;
        std::vector<std::string> main_menu_options;
        std::vector<std::string> vertex_menu_options;
        std::vector<std::string> edge_menu_options;
    public:

    UI(Graph& graph);
    ~UI();

    void print_main_menu();
    void print_edge_menu();
    void print_vertex_menu();

    void get_properties_of_graph();

    void display_vertices();
    void add_vertex();
    void remove_vertex();
    void get_in_degree();
    void get_out_degree();
    void iterate_vertices();

    bool vertex_menu();

    void display_edges();
    void add_edge();
    void remove_edge();
    void edit_edge_cost();
    void get_edge_properties();
    void check_if_edge_exists();
    void iterate_edges();

    bool edge_menu();

    void save_to_file();
    void random_graph();

    bool main_menu();



};