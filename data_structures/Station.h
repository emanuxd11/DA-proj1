//
// Created by manu on 3/15/23.
//

#ifndef PROJETO1_STATION_H
#define PROJETO1_STATION_H


class Station {
public:
    // adicionar métodos aqui
    void setName(string name);
    void setDistrict(string district);
    void setMunicipality(string municipality);
    void setTownship(string township);
    void setLine(string line);

    string getName();
    string getDistrict();
    string getMunicipality();
    string getTownship();
    string getLine();
private:
    string name;
    string district;
    string municipality;
    string township;
    string line;
};


#endif //PROJETO1_STATION_H
