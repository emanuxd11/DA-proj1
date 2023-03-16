//
// Created by manu on 3/15/23.
//

#include "Station.h"

void Station::setName(std::string name) {
    this->name = name;
}

void Station::setDistrict(std::string district) {
    this->district = district;
}

void Station::setTownship(std::string township) {
    this->township = township;
}

void Station::setMunicipality(std::string municipality) {
    this->municipality = municipality;
}

void Station::setLine(std::string line) {
    this->line = line;
}


std::string Station::getName() {
    return this->name;
}

std::string Station::getDistrict() {
    return this->district;
}

std::string Station::getMunicipality() {
    return this->municipality;
}

std::string Station::getTownship() {
    return this->township;
}

std::string Station::getLine() {
    return this->line;
}
