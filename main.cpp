#include <iostream>
#include <unordered_map>
#include <sstream>
#include "includes/Graph.h"
#include "includes/Database.h"
#include "includes/Station.h"

using namespace std;

int main() {
    Database db;
    unordered_map<int, Station> stationHash = db.loadStations();
    unordered_map<string, int> inverseHash = db.stationsByName(stationHash);
    Graph g = db.loadGraph(stationHash);

    // test
    for (Vertex *v : g.getVertexSet()) {
        for (Edge *edge : v->getAdj()) {
            cout << stationHash[edge->getDest()->getId()].getName() << endl;
        }
    }

    return 0;
}
