//
// Created by manu on 3/15/23.
//

#include "Database.h"

std::unordered_map<int, Station> Database::loadStations() {
    std::unordered_map<int, Station> stationHash;

    std::ifstream stations("../stations.csv");

    if (stations.is_open()) {
        int count = 0;
        Station station;
        std::string row, name, district, municipality, township, line, throwaway;
        getline(stations, throwaway);
        while (getline(stations, row)) {
            std::stringstream sep(row);
            getline(sep, name, ',');
            getline(sep, district, ',');
            getline(sep, municipality, ',');
            getline(sep, township, ',');
            getline(sep, line, '\n');

            station.setName(name);
            station.setDistrict(district);
            station.setMunicipality(municipality);
            station.setTownship(township);
            station.setLine(line);

            stationHash[count] = station;
            count++;
        }
    }

    return stationHash;
}

std::unordered_map<std::string, int> Database::stationsInverse(std::unordered_map<int, Station> stationHash) {
    std::unordered_map<std::string, int> inverse;

    for (auto &it : stationHash) {
        inverse[it.second.getName()] = it.first;
    }
    return inverse;
}

Graph Database::loadGraph(std::unordered_map<int, Station> stationHash) {
    Graph g;
    std::ifstream network("../network.csv");

    if (network.is_open()) {
        std::unordered_map<std::string, int> inverseStations = stationsInverse(stationHash);

        std::string line, origStation, destStation, capacity, throwaway;

        getline(network, throwaway);
        while (getline(network, line)) {
            std::stringstream sep(line);
            getline(sep, origStation, ',');
            getline(sep, destStation, ',');
            getline(sep, capacity, ',');
            getline(sep, line, '\n');

            int origId = inverseStations[origStation];
            int destId = inverseStations[destStation];
            Station orig = stationHash[origId];
            Station dest = stationHash[destId];

            g.addVertex(origId, orig);
            g.addVertex(destId, dest);
            g.addEdge(orig, dest, std::stod(capacity));
        }
    }

    return g;
}
