//
// Created by manu on 3/15/23.
//

#ifndef PROJETO1_DATABASE_H
#define PROJETO1_DATABASE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Station.h"
#include "Graph.h"
#include <regex>

class Database {
public:
    std::unordered_map<int, Station> loadStations();

    Graph loadGraph(std::unordered_map<int, Station>& stationHash);

    static std::unordered_map<std::string, int> stationsByName(std::unordered_map<int, Station> stationHash);


private:
    //
};


#endif //PROJETO1_DATABASE_H
