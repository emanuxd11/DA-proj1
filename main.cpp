#include <iostream>
#include <unordered_map>

#include "data_structures/Graph.h"
#include "data_structures/Database.h"
#include "data_structures/VertexEdge.h"

int main() {
    Database db;
    std::unordered_map<int, Station> stationHash = db.loadStations();

    Graph g = db.loadGraph(stationHash);

    for (auto v : g.getVertexSet()) {
        for (auto e : v->getAdj()) {
            std::cout << e->getOrig()->getStation().getName() << "->" << e->getDest()->getStation().getName() << std::endl;
        }
    }

    return 0;
}
