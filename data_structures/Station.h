//
// Created by manu on 3/15/23.
//

#ifndef PROJETO1_STATION_H
#define PROJETO1_STATION_H

#include <string>

class Station {
public:
    void setName(std::string name);

    void setDistrict(std::string district);

    void setMunicipality(std::string municipality);

    void setTownship(std::string township);

    void setLine(std::string line);

    std::string getName();

    std::string getDistrict();

    std::string getMunicipality();

    std::string getTownship();

    std::string getLine();

private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
};


#endif //PROJETO1_STATION_H
