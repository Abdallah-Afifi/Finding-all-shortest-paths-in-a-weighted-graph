// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

// Define the maximum number of vertices and edges
const int Vmax = 50;
const int Emax = Vmax * (Vmax - 1) / 2;

// Define the Edge class to represent an edge in the graph
class Edge {
public:
    int u, v, w; // vertices u and v, and weight w

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

class Graph {
public:
    Graph(const std::vector<Edge>& edges, int numVertices, const std::vector<std::string>& cityNames);

    void DFS(int startCityIndex) const;
    void Dijkstra(int startCityIndex) const;

private:
    std::vector<std::vector<int>> adjacencyMatrix;
    std::vector<Edge> edges;
    std::vector<std::string> cityNames;

    void DFSHelper(int cityIndex, std::vector<bool>& visited) const;
    int getMinDistance(const std::vector<int>& distances, const std::vector<bool>& visited) const;
    void printPath(const std::vector<int>& parents, int currentCityIndex) const;
};

#endif // GRAPH_H
