cmake_minimum_required(VERSION 3.17)
project(Projeto1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto1 main.cpp
        data_structures/Station.cpp
        data_structures/Database.cpp
        data_structures/Graph.h)