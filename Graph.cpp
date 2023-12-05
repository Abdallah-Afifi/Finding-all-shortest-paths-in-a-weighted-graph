// Graph.cpp
#include "Graph.h"
#include <iostream>
#include <climits>
#include <vector>
#include <stack>

Graph::Graph(const std::vector<Edge>& edges, int numVertices, const std::vector<std::string>& cityNames)
    : edges(edges), cityNames(cityNames) {

    // Initialize the adjacency matrix with zeros
    adjacencyMatrix.resize(Vmax, std::vector<int>(Vmax, 0));

    // Populate the adjacency matrix with edge weights
    for (const Edge& edge : edges) {
        adjacencyMatrix[edge.u][edge.v] = edge.w;
        adjacencyMatrix[edge.v][edge.u] = edge.w; // Assuming an undirected graph
    }
}

void Graph::DFSHelper(int cityIndex, std::vector<bool>& visited) const {
    visited[cityIndex] = true;
    std::cout << cityNames[cityIndex] << " ";

    for (int i = 0; i < Vmax; ++i) {
        if (adjacencyMatrix[cityIndex][i] && !visited[i]) {
            DFSHelper(i, visited);
        }
    }
}

void Graph::DFS(int startCityIndex) const {
    std::vector<bool> visited(Vmax, false);
    std::cout << "DFS traversal starting from city " << cityNames[startCityIndex] << ":\n";
    DFSHelper(startCityIndex, visited);
    std::cout << "\n";
}

void Graph::Dijkstra(int startCityIndex) const {
    int numCities = cityNames.size();

    std::vector<int> distances(numCities, INT_MAX);
    std::vector<bool> visited(numCities, false);
    std::vector<int> parents(numCities, -1);

    distances[startCityIndex] = 0;

    for (int i = 0; i < numCities - 1; ++i) {
        int minDistanceIndex = getMinDistance(distances, visited);
        visited[minDistanceIndex] = true;

        for (int j = 0; j < numCities; ++j) {
            if (!visited[j] && adjacencyMatrix[minDistanceIndex][j] &&
                distances[minDistanceIndex] != INT_MAX &&
                distances[minDistanceIndex] + adjacencyMatrix[minDistanceIndex][j] < distances[j]) {
                distances[j] = distances[minDistanceIndex] + adjacencyMatrix[minDistanceIndex][j];
                parents[j] = minDistanceIndex;
            }
        }
    }

    // Print the shortest paths
    std::cout << "\nShortest Paths from Node " << cityNames[startCityIndex] << "\n";
    for (int i = 0; i < numCities; ++i) {
        std::cout << "" << distances[i] << " " << cityNames[startCityIndex];
        printPath(parents, i);
        std::cout << "\n";
    }
}

int Graph::getMinDistance(const std::vector<int>& distances, const std::vector<bool>& visited) const {
    int minDistance = INT_MAX, minDistanceIndex = -1;
    int numCities = distances.size();

    for (int i = 0; i < numCities; ++i) {
        if (!visited[i] && distances[i] <= minDistance) {
            minDistance = distances[i];
            minDistanceIndex = i;
        }
    }

    return minDistanceIndex;
}

void Graph::printPath(const std::vector<int>& parents, int currentCityIndex) const {
    if (parents[currentCityIndex] == -1) {
        return;
    }

    printPath(parents, parents[currentCityIndex]);
    std::cout << "" << cityNames[currentCityIndex];
}
