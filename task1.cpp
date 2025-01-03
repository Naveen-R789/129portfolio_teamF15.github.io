//Business Case  (Last-Mile Connectivity)
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>

using namespace std;

// Abstract Data Type for Graph
class Graph {
private:
    unordered_map<string, vector<pair<string, int>>> adjList; // Adjacency list

public:
    // Add an edge to the graph
    void addEdge(const string& source, const string& destination, int weight) {
        adjList[source].push_back({destination, weight});
        adjList[destination].push_back({source, weight}); // For undirected graph
    }

    // Get neighbors of a node
    const vector<pair<string, int>>& getNeighbors(const string& node) const {
        return adjList.at(node);
    }

    // Check if a node exists in the graph
    bool hasNode(const string& node) const {
        return adjList.find(node) != adjList.end();
    }
};

// Function to find the shortest path using Dijkstra's Algorithm
unordered_map<string, int> dijkstra(const Graph& graph, const string& startNode) {
    unordered_map<string, int> distances;
    unordered_map<string, bool> visited;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    // Initialize distances to infinity
    for (const auto& node : graph.getNeighbors(startNode)) {
        distances[node.first] = numeric_limits<int>::max();
    }

    distances[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [currentDistance, currentNode] = pq.top();
        pq.pop();

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        for (const auto& [neighbor, weight] : graph.getNeighbors(currentNode)) {
            if (!visited[neighbor]) {
                int newDistance = currentDistance + weight;

                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.push({newDistance, neighbor});
                }
            }
        }
    }

    return distances;
}

int main() {
    Graph cityGraph;

    // Example edges representing connectivity between areas
    cityGraph.addEdge("CentralStation", "CommunityA", 5);
    cityGraph.addEdge("CentralStation", "CommunityB", 10);
    cityGraph.addEdge("CommunityA", "CommunityC", 3);
    cityGraph.addEdge("CommunityB", "CommunityD", 7);
    cityGraph.addEdge("CommunityC", "CommunityD", 2);

    string startNode = "CentralStation";

    if (!cityGraph.hasNode(startNode)) {
        cout << "Error: Start node does not exist in the graph." << endl;
        return 1;
    }

    unordered_map<string, int> shortestPaths = dijkstra(cityGraph, startNode);

    cout << "Shortest distances from " << startNode << ":\n";
    for (const auto& [node, distance] : shortestPaths) {
        cout << node << ": " << distance << "\n";
    }

    return 0;
}


