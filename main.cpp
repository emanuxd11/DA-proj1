#include <iostream>
#include <unordered_map>

#include "data_structures/Graph.h"
#include "data_structures/Database.h"
#include "data_structures/VertexEdge.h"


Graph loadData() {
    Database db;
    std::unordered_map<int, Station> stationHash = db.loadStations();
    Graph g = db.loadGraph(stationHash);
    return g;
}

// t2.2
void highestCapPair() {
    // Determine, from all pairs of stations, which ones (if more than one) require the
    // most amount of trains when taking full advantage of the existing network capacity
}

int main() {
    std::vector<std::string> options = {"load data", "option 2"};
    Graph g;
    int option;

    for (auto it = options.begin(); it != options.end(); it++) {
        std::cout << std::distance(options.begin(), it) + 1 << " - " << *it << std::endl;
    }
    std::cin >> option;

    switch (option) {
        case 1:
            g = loadData();
            break;
        case 2:
            // do something
            break;
        default:
            // do something
            break;
    }

    /* for (auto v : g.getVertexSet()) {
        for (auto e : v->getAdj()) {
            std::cout << e->getOrig()->getStation().getName() << "->" << e->getDest()->getStation().getName() << std::endl;
        }
    } */

    return 0;
}
