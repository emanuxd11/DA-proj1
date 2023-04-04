// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"
#include "Station.h"
#include <unordered_map>

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();

    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, int w, int c);

    bool addBidirectionalEdge(const int &sourc, const int &dest, int w, int c);

    int getNumVertex() const;

    std::vector<Vertex *> getVertexSet() const;

    void setStationHash(std::unordered_map<int, Station> const &stations);

    void setInvertedHash(std::unordered_map<std::string, int> const &stationsInverse);

    std::unordered_map<int, Station> getStationHash();

    std::unordered_map<std::string, int> getInvertedHash();

    int maxFlowStations(int source, int target);

    int dijkstra(Vertex* src, Vertex* dest);

    std::pair<int, int> maxTrainMinCost(int source, int target);

    bool empty();
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    // para aceder mais facilmente às estações, inseri aqui os mapas
    std::unordered_map<int, Station> stationHash;
    std::unordered_map<std::string, int> inverseHash;

    int **distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;

    bool findAugmentingPath(Vertex *s, Vertex *t);
};

void deleteMatrix(int **m, int n);

void deleteMatrix(int **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */