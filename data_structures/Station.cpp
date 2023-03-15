//
// Created by manu on 3/15/23.
//

#include "Station.h"

void Station::setName(string name) {
    this->name = name;
}

void Station::setDistrict(string district) {
    this->district = district;
}

void Station::setTownship(string township) {
    this->township = township;
}

void Station::setMunicipality(string municipality) {
    this->municipality = municipality;
}

void Station::setLine(string line) {
    this->line = line;
}


string Station::getName() {
    return this->name;
}

string Station::getDistrict() {
    return this->district;
}

string Station::getMunicipality() {
    return this->municipality;
}

string Station::getTownship() {
    return this->township;
}

string Station::getLine() {
    return this->line;
}
