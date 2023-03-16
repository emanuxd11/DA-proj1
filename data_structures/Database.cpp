//
// Created by manu on 3/15/23.
//

#include "Database.h"

std::unordered_map<int, Station> Database::loadStations() {
    std::unordered_map<int, Station> stationHash;

    std::ifstream stations("stations.csv");

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

    for (auto it = stationHash.begin(); it != stationHash.end(); it++) {
        inverse[it->second.getName()] = it->first;
    }
    return inverse;
}

Graph Database::loadGraph(Graph &g, std::unordered_map<int, Station> stationHash) {

    std::ifstream network("network.csv");

    if (network.is_open()) {
        // Edge *edge;
        std::unordered_map<std::string, int> inverseStations = stationsInverse(stationHash);

        std::string line, origStation, destStation, capacity, throwaway;
        int origId, destId;

        getline(network, throwaway);
        while (getline(network, line)) {
            std::stringstream sep(line);
            getline(sep, origStation, ',');
            getline(sep, destStation, ',');
            getline(sep, capacity, ',');
            getline(sep, line, '\n');

            origId = inverseStations[origStation];
            destId = inverseStations[destStation];

            g.addEdge(origId, destId, std::stod(capacity));
        }
    }
}
