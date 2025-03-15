#include "dijkstras.h"
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

struct Node{
    int vertex;
    int cost;
    Node(int v, int c) : vertex(v), cost(c) {}
};

struct NodeComparator{
    bool operator()(const Node &a, const Node &b){ return a.cost > b.cost; }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    
    std::priority_queue<Node, vector<Node>, NodeComparator> pq;
    distance[source] = 0;
    pq.push(Node(source, 0));
    
    while(!pq.empty()){
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if(visited[u])
            continue;
        visited[u] = true;
        for(const auto &edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    if(distances[destination] == INF){ return path; }
    for(int at = destination; at != -1; at = previous[at]){
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total){
    for(size_t i=0; i<path.size(); ++i){
        std::cout << path[i];
        if(i != path.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}
