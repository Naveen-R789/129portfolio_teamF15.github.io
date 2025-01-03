//Business Case  (inclusive mobility for all)
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// Abstract Data Type for City Transport Graph
class CityTransport {
private:
    int areas; // Number of areas in the city
    std::vector<std::vector<std::pair<int, int>>> transportNetwork; // Adjacency list (area, weight)

public:
    CityTransport(int a) : areas(a), transportNetwork(a) {}

    void addRoute(int fromArea, int toArea, int cost) {
        transportNetwork[fromArea].emplace_back(toArea, cost);
        transportNetwork[toArea].emplace_back(fromArea, cost);
    }

    // Prim's Algorithm to find Minimum Spanning Tree (MST)
    void optimizeTransportNetwork() {
        std::vector<int> minCost(areas, INT_MAX); // Minimum cost to include an area
        std::vector<bool> includedInMST(areas, false); // To check if area is in MST
        std::vector<int> parent(areas, -1); // To store MST structure

        // Priority queue to select route with minimum cost
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        minCost[0] = 0; // Start from the first area
        pq.push({0, 0}); // (cost, area)

        while (!pq.empty()) {
            int currentArea = pq.top().second;
            pq.pop();

            if (includedInMST[currentArea]) continue;
            includedInMST[currentArea] = true;

            for (const auto &neighbor : transportNetwork[currentArea]) {
                int adjacentArea = neighbor.first;
                int routeCost = neighbor.second;

                if (!includedInMST[adjacentArea] && routeCost < minCost[adjacentArea]) {
                    minCost[adjacentArea] = routeCost;
                    pq.push({minCost[adjacentArea], adjacentArea});
                    parent[adjacentArea] = currentArea;
                }
            }
        }

        // Output MST
        std::cout << "Optimized Transport Routes in the City:\n";
        for (int i = 1; i < areas; ++i) {
            if (parent[i] != -1) {
                std::cout << "Area " << parent[i] << " - Area " << i << "\n";
            }
        }
    }
};

int main() {
    int areas, routes;
    std::cout << "Enter the number of areas in the city: ";
    std::cin >> areas;
    std::cout << "Enter the number of transport routes: ";
    std::cin >> routes;

    CityTransport cityTransport(areas);

    std::cout << "Enter the transport routes (fromArea toArea cost):\n";
    for (int i = 0; i < routes; ++i) {
        int fromArea, toArea, cost;
        std::cin >> fromArea >> toArea >> cost;
        cityTransport.addRoute(fromArea, toArea, cost);
    }

    std::cout << "\nOptimizing city transport network using Prim's algorithm...\n";
    cityTransport.optimizeTransportNetwork();

    return 0;
}
