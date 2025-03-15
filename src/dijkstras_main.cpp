#include "dijkstras.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " graph_file" << endl;
        return 1;
    }
    
    string filename = argv[1];
    Graph G;
    file_to_graph(filename, G);
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    for(auto v : G.numVertices){
        vector<int> path = extract_shortest_path(distances, previous, v);
        if (path.empty()){ cout << "No path from 0 to " << v << endl; } 
        else { print_path(path, distances[v]); }
    }
    
    return 0;
}
