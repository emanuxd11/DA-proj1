#include <iostream>
#include <unordered_map>

#include "includes/Graph.h"
#include "includes/Database.h"
#include "includes/Station.h"


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
