//
// Created by manu on 3/15/23.
//

#ifndef PROJETO1_DATABASE_H
#define PROJETO1_DATABASE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Station.h"
#include <Graph.h>

class Database {
public:
    unordered_map<int, Station> loadStations();
    Graph loadGraph();

private:

};


#endif //PROJETO1_DATABASE_H
