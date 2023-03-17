cmake_minimum_required(VERSION 3.24)
project(DA_proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_proj1 main.cpp data_structures/Graph.cpp data_structures/Heap.cpp data_structures/Station.cpp data_structures/UFDS.cpp data_structures/VertexEdge.cpp data_structures/Database.cpp)
