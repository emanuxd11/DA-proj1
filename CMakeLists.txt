cmake_minimum_required(VERSION 3.17)
project(DA_proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_proj1 src/main.cpp
        src/Graph.cpp includes/Graph.h
        src/Heap.cpp includes/Heap.h
        src/Station.cpp includes/Station.h
        src/UFDS.cpp includes/UFDS.h
        src/VertexEdge.cpp includes/VertexEdge.h
        src/Database.cpp includes/Database.h
        )
