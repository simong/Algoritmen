#include <vector>
#include <stack>

enum Color {
    WHITE, GRAY, BLACK
};

template<unsigned int m>
class Graph {
public:
    Graph();

    // Add an edge between two vertices.
    void connect(unsigned int from, unsigned int to);

    // Remove an edge
    void remove(unsigned int from, unsigned int to);

    // Returns the eulerian cycle
    std::vector<unsigned int> euler();

//private:
    // Finds a cycle starting at a vertex.
    // it will append that cycle to the unvisited stack.
    bool find_cycle(unsigned int vertex, std::stack<unsigned int>& unvisited);
    bool visit(unsigned int vertex, Color *visited, std::stack<unsigned int>& unvisited,
            unsigned int start);

    unsigned int graph[m][m];
};

template<unsigned int m>
Graph<m>::Graph() {
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < m; j++) {
            graph[i][j] = 0;
        }
    }
}

template<unsigned int m>
void Graph<m>::connect(unsigned int from, unsigned int to) {
    graph[from][to]++;
    graph[to][from]++;
}
template<unsigned int m>
void Graph<m>::remove(unsigned int from, unsigned int to) {
    graph[from][to]--;
    graph[to][from]--;
}

template<unsigned int m>
std::vector<unsigned int> Graph<m>::euler() {
    // This vector will hold the vertexes necessary to create a eulerian path.
    // Essentially this will be one big cycle.
    std::vector<unsigned int> path;

    // Start at a random vertex. (might as well start at 0)
    // Do a depth-search to find an initial cycle.
    // Stick the vertexes of that cycle on a stack.
    unsigned int visit_vertex = 0;
    std::stack<unsigned int> unvisited;
    find_cycle(visit_vertex, unvisited);

    // As long as we haven't visited a vertex, we need to keep going.
    while (!unvisited.empty()) {
        visit_vertex = unvisited.top();
        unvisited.pop();

        // This is one vertex we'll need.
        path.push_back(visit_vertex);

        // There might be a cycle on this vertex.
        // If there is we'll look it up and ADD it to the stack.
        find_cycle(visit_vertex, unvisited);
    }

    return path;
}

template<unsigned int m>
bool Graph<m>::find_cycle(unsigned int vertex, std::stack<unsigned int>& unvisited) {
    // We can find a cycle quite easily by performing a DFS (Depth First Search)
    // on the vertex.
    Color visited[m];
    for (unsigned int i = 0; i < m; i++) {
        visited[i] = WHITE;
    }

    // Visit the 'start' vertex.
    return visit(vertex, visited, unvisited, vertex);
}

template<unsigned int m>
bool Graph<m>::visit(unsigned int vertex, Color *visited,
        std::stack<unsigned int>& unvisited, unsigned int start) {
    // A new vertex.
    unsigned int predecessor = vertex;
    if (!unvisited.empty())
        predecessor = unvisited.top();
    visited[vertex] = GRAY;
    unvisited.push(vertex);
    bool found_cycle = false;

    // Now visit all the neighbours.
    unsigned int i = 0;
    while (!found_cycle && i < m) {
        if (graph[vertex][i] > 0) {
            // Take out that edge
            remove(vertex, i);

            // If we've already visited this vertex
            // Than we've found a cycle
            // Make sure that we're not finding a cycle between a vertex and it's predecessor.
            if (i == start && predecessor != i) {
                return true;
            }
            else if (visited[i] == WHITE) {
                found_cycle = visit(i, visited, unvisited, start);
            }
        }
        i++;
    }

    if (!found_cycle) {
        unvisited.pop();
    }
    return found_cycle;
}
