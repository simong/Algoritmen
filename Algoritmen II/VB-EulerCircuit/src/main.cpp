#include<iostream>
#include<vector>

#include "graph.h"

/**
 * Attempt at finding an euler circuit in a undirected graph.
 */

template<unsigned int m>
void create_graph(Graph<m>& graph) {
    // Outer edges.
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(5, 0);
    // Vertical edges
    graph.connect(1, 5);
    graph.connect(2, 4);
    // cross edges
    graph.connect(1, 4);
    graph.connect(2, 5);
}

int main() {

    Graph<6> graph;
    create_graph<6>(graph);

    //graph.euler();

    std::vector<unsigned int> path = graph.euler();
    for (unsigned int i = 0; i < path.size();i++) {
        std::cout << path[i] << " ";
    }
    return 0;
}
