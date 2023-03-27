#include <iostream>
#include <unordered_map>

#include "includes/Graph.h"
#include "includes/Database.h"
#include "includes/Station.h"

using namespace std;

Graph getGraph() {
    Database db;
    std::unordered_map<int, Station> stationHash = db.loadStations();
    return db.loadGraph(stationHash);
}

int main() {
    Database db;
    unordered_map<int, Station> stationHash = db.loadStations();
    unordered_map<string, int> inverseHash = db.stationsInverse(stationHash);
    Graph g = db.loadGraph(stationHash);

    for (Vertex *v : g.getVertexSet()) {
    //    cout << stationHash[v->getId()].getTownship() << endl;
    }

    string line = "\"some\",\"comma\",\"sepa,rated\",\"words\"";
    vector <string> tokens;
    stringstream check1(line);
    string intermediate;
    while(!check1.eof()) {
        if (check1.str().front() == '"' ) {
            check1.str(check1.str().substr(1));
            getline(check1, intermediate, '"');
        } else {
            getline(check1, intermediate, ',');
        }

        if (!intermediate.empty()) {
            tokens.push_back(intermediate);
        }

        if (intermediate.size() + 1 < check1.str().size()) {
            check1.str(check1.str().substr(intermediate.size() + 1));
        }
    }

    for (auto token : tokens) {
        cout << token << ",";
    }

    return 0;
}
