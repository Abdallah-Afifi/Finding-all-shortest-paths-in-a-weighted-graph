// main.cpp
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Function to read a CSV file and return the adjacency matrix
std::vector<std::vector<int>> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> matrix;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<int> row;
            int value;

            while (iss >> value) {
                row.push_back(value);
                if (iss.peek() == ',')
                    iss.ignore();
            }

            matrix.push_back(row);
        }
        file.close();
    }

    return matrix;
}

int main() {
    // Read the CSV files
    std::vector<std::vector<int>> testGraphMatrix = readCSV("TestG.txt");
    std::vector<std::vector<int>> citiesGraphMatrix = readCSV("CitiesG.txt");

    // Create edges for the graphs
    std::vector<Edge> testGraphEdges;
    std::vector<Edge> citiesGraphEdges;

    for (int i = 0; i < testGraphMatrix.size(); ++i) {
        for (int j = 0; j < testGraphMatrix[i].size(); ++j) {
            if (testGraphMatrix[i][j] != 0) {
                testGraphEdges.push_back(Edge(i, j, testGraphMatrix[i][j]));
            }
        }
    }

    for (int i = 0; i < citiesGraphMatrix.size(); ++i) {
        for (int j = 0; j < citiesGraphMatrix[i].size(); ++j) {
            if (citiesGraphMatrix[i][j] != 0) {
                citiesGraphEdges.push_back(Edge(i, j, citiesGraphMatrix[i][j]));
            }
        }
    }

    // Create the Graph objects
    Graph testGraph(testGraphEdges, testGraphMatrix.size(), {"A", "B", "C", "D", "E", "F", "G"});
    Graph citiesGraph(citiesGraphEdges, citiesGraphMatrix.size(),
                      {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"});

    // Test DFS
    testGraph.DFS(0);
    std::cout << std::endl;
    testGraph.Dijkstra(0);
    std::cout << std::endl;

    // Test Dijkstra
    citiesGraph.DFS(0);
    std::cout << std::endl;
    citiesGraph.Dijkstra(0);
    std::cout << std::endl;

    return 0;
}
