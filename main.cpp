#include <iostream>
#include <unordered_map>

#include "includes/Graph.h"
#include "includes/Database.h"
#include "includes/Station.h"

using namespace std;


int main() {
    Database db;
    std::unordered_map<int, Station> stationHash = db.loadStations();

    Graph g;
    db.loadGraph(g, stationHash);

    /*for (auto station : stationHash) {
        std::cout << station.second.getName() << std::endl;
    }*/

   /* for (auto v : g.getVertexSet()) {
        //Station st = stationHash[v->getId()];
        //std::cout << st.getName() << std::endl;

        if (g.findVertex(stati))
            cout << "Not Present " << v->getId() << endl;

        //std::cout << v->getId() << std::endl;
    }*/

    //unordered_map<std::string, int> stationAux = db.stationsInverse(stationHash);

    /*for(int i = 0; i < stationHash.size(); i++){
        Station st = stationHash[i];
        //int id = stationAux[st.getName()];
        if(g.findVertex(i) == nullptr)
            cout << "Not Present " << i  << " " << st.getName() << endl;
    }*/

    //std::cout << g.getNumVertex() << std::endl;
    //std::cout << stationHash.size() << std::endl;

    return 0;
}
