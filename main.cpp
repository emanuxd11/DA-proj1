#include <iostream>
#include <unordered_map>

#include "data_structures/Graph.h"
#include "data_structures/Database.h"


int main() {
    Database db;
    std::unordered_map<int, Station> stationHash = db.loadStations();

    Graph g = db.loadGraph(stationHash);

    for (auto station : stationHash) {
        std::cout << station.second.getName() << std::endl;
    }

    /* for (auto v : g.getVertexSet()) {
        std::cout << v->getId() << std::endl;
    } */

    return 0;
}
