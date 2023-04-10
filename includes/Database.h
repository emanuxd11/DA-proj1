//
// Created by manu on 3/15/23.
//

#ifndef PROJETO1_DATABASE_H
#define PROJETO1_DATABASE_H

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include "Station.h"
#include "Graph.h"
#include <regex>

class Database {
public:
    // static std::unordered_map<int, Station> loadStations();

    static Graph loadGraph();

    static Graph loadGraph(std::vector<std::pair<std::string, std::string>> exclude);

    static std::unordered_map<int, Station> loadStations(std::unordered_set<std::string> &districts, std::unordered_set<std::string> &municipalities);

    static std::unordered_map<std::string, int> stationsByName(std::unordered_map<int, Station> stationHash);
private:
    // std::unordered_map<int, Station> districts;

    static std::unordered_set<std::string> districts;
    //
};


#endif //PROJETO1_DATABASE_H
