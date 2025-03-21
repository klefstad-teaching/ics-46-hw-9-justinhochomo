#include "dijkstras.h"

int main() {
    Graph G;

    file_to_graph("small.txt", G);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    for (int dest = 0; dest < G.numVertices; ++dest) {
        vector<int> path = extract_shortest_path(distances, previous, dest);
        print_path(path, distances[dest]);
    }

    return 0;
}
