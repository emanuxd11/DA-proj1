#include <iostream>
#include "data_structures/Station.h"

int main() {
    Station station;
    station.setName("abc");
    std::cout << station.getName() << std::endl;
    return 0;
}
