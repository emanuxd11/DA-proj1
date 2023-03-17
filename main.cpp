#include <iostream>
#include "data_structures/Station.h"

int main() {
    Station stat;
    stat.setName("hello does this work!!??");
    std::cout << stat.getName() << std::endl;
    return 0;
}
