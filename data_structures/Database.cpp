//
// Created by manu on 3/15/23.
//

#include "Database.h"

unordered_map<int, Station> Database::loadStations() {
    unordered_map<int, Station> stationHash;

    ifstream stations("stations.csv");

    if (stations.is_open()) {
        int count = 0;
        Station station;
        string row, name, district, municipality, township, line, throwaway;
        getline(stations, throwaway);
        while (getline(stations, row)) {
            stringstream sep(row);
            getline(sep, name, ",");
            getline(sep, district, ",");
            getline(sep, municipality, ",");
            getline(sep, township, ",");
            getline(sep, line, "\n");

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

unordered_map<string, int> Database::stationsInverse(unordered_map<Station, int> stationHash) {
    unordered_map<string, int> inverse;
    unordered_map<int, string>::iterator it;

    for (it = stationHash.begin(); it != stationHash.end(), it++) {
        inverse[it->second.getName()] = it->first;
    }
    return inverse;
}

Graph Database::loadGraph(Graph &g, unordered_map<int, Station> stationHash) {

    ifstream network("network.csv");

    if (network.is_open()) {
        int count = 0;
        Edge *edge;
        unordered_map<string, int> inverseStations = stationsInverse(stationHash);

        string line, origStation, destStation, capacity, throwaway;
        int origId, destID;

        getline(network, throwaway);
        while (getline(network, line)) {
            stringstream sep(line);
            getline(sep, origStation, ",");
            getline(sep, destStation, ",");
            getline(sep, capacity, ",");
            getline(sep, line, "\n");

            origId = inverseStations[origStation];
            destId = inverseStations[destStation];

            g.addEdge(origId, destID, (double)capacity);
        }
    }
}
