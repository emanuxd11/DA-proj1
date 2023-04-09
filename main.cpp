#include <iostream>
#include <unordered_map>
#include <map>
#include "includes/Graph.h"
#include "includes/VertexEdge.h"
#include "includes/Database.h"
#include "includes/Station.h"

using namespace std;

// opção 1
Graph initGraph() {
    Database db;
    return Database::loadGraph();
}

// opção 2
bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for (auto v: vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            int residual = e->getCapacity() - e->getFlow();
            if (!w->isVisited() && residual > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
        for (auto e: v->getIncoming()) {
            auto w = e->getOrig();
            int residual = e->getFlow();
            if (!w->isVisited() && residual > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }
    return t->isVisited();
}

int Graph::maxFlowStations(int source, int target) {
    int res = 0.0;
    Vertex *s = findVertex(source);
    Vertex *t = findVertex(target);

    if (s == nullptr || t == nullptr || s == t) {
        throw std::logic_error("Invalid source and/or target vertex");
    }

    // Reset the flows
    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    // Loop to find augmentation paths
    while (findAugmentingPath(s, t)) {
        int f = UINT8_MAX;
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                f = std::min(f, e->getCapacity() - e->getFlow());
                v = e->getOrig();
            } else {
                f = std::min(f, e->getFlow());
                v = e->getDest();
            }
        }
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            int flow = e->getFlow();
            if (e->getDest() == v) {
                e->setFlow(flow + f);
                v = e->getOrig();
            } else {
                e->setFlow(flow - f);
                v = e->getDest();
            }
        }
        res += f;
    }

    return res;
}

// opção 3
struct solution3 {
    vector<vector<Station>> station_pairs;
    int maxFlow;
};

solution3 largestCapPair(Graph network) {
    solution3 res;
    res.maxFlow = -1;
    unordered_map<int, Station> stations = network.getStationHash();

    for (int i = 0; i < network.getVertexSet().size(); i++) {
        if (!network.findVertex(i)) continue;
        for (int j = i + 1; j < network.getVertexSet().size(); j++) {
            if (!network.findVertex(j)) continue;

            int flow = network.maxFlowStations(i, j);
            if (flow == res.maxFlow) {
                res.station_pairs.push_back({stations[i], stations[j]});
            } else if (flow > res.maxFlow) {
                res.station_pairs.erase(res.station_pairs.begin(), res.station_pairs.end());
                res.station_pairs.push_back({stations[i], stations[j]});
                res.maxFlow = flow;
            }
        }
    }

    return res;
}

unsigned transportationNeed(Graph &network, string const &district) {
    int superSourceId = -1;
    int superSinkId = network.getNumVertex();

    vector<int> in;
    vector<int> out;

    network.addVertex(superSourceId);
    network.addVertex(superSinkId);

    std::unordered_map<int, Station> stations = network.getStationHash();

    for (auto v: network.getVertexSet()) {
        if (v->getId() == superSourceId || v->getId() == superSinkId) continue;

        if (stations[v->getId()].getDistrict() == district) {
            network.addEdge(v->getId(), superSinkId, INF, 0);
            out.push_back(v->getId());
        } else if (v->getAdj().size() == 1) {
            network.addEdge(superSourceId, v->getId(), INF, 0);
            in.push_back(v->getId());
        }
    }

    int maxFlow = network.maxFlowStations(superSourceId, superSinkId);

    for (int id: in) {
        network.findVertex(superSourceId)->removeEdge(id);
    }

    for (int id: out) {
        network.findVertex(id)->removeEdge(superSinkId);
    }

    network.deleteVertex(superSourceId);
    network.deleteVertex(superSinkId);

    return maxFlow;
}


// opção 4
void topKMunDistr(Graph &network, unsigned k) {
    vector<pair<string, int>> district_res;
    vector<pair<string, int>> municip_res;

    unordered_set<string> districts = network.getDistricts();
    unordered_set<string> municipalities = network.getMunicipalities();

    for (const string &district: districts) {
        district_res.emplace_back(district, transportationNeed(network, district));
    }

    sort(district_res.begin(), district_res.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second;
    });

    cout << "The top " << k << " districts are:" << endl;
    for (auto it = district_res.begin(); it != district_res.begin() + k && it != district_res.end(); ++it) {
        cout << it->first << " -> " << it->second << endl;
    }
}


// opção 5
int maxSimTrainStation(Graph network, string const &station_name) {
    int super_source_ID = -1;
    vector<int> ids;
    network.addVertex(super_source_ID);

    for (auto v: network.getVertexSet()) {
        if (v->getAdj().size() == 1) {
            network.addEdge(super_source_ID, v->getId(), INF, v->getAdj()[0]->getCost());
            ids.push_back(v->getId());
        } else if (v->getAdj().size() == 2) {
            if (v->getAdj()[0]->getCost() != v->getAdj()[1]->getCost()) {
                network.addEdge(super_source_ID, v->getId(), INF, v->getAdj()[0]->getCost());
                network.addEdge(super_source_ID, v->getId(), INF, v->getAdj()[1]->getCost());
                ids.push_back(v->getId());
            }
        }
    }

    int maxFlow = network.maxFlowStations(super_source_ID, network.getInvertedHash()[station_name]);
    for (int id: ids) {
        network.findVertex(super_source_ID)->removeEdge(id);
    }

    return maxFlow;
}

/**
 * This function compares two vertices and sorts them.
 */
struct CompareVertex {
    bool operator()(Vertex *v1, Vertex *v2) {
        return v1->getDist() > v2->getDist();
    }
};

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm.  The
// function also detects negative capacity cycle
/**
 * This algorithm finds the shortest path from a vertex which is the source node to all other vertices in a weighted graph
 * with non-negative edge weights.
 * Time Complexity: O((V+E)log V)
 * @param src Vertex, source node
 * @param dest Vertex, destination node
 * @return dist[dest], represents the distance of the source vertex src to the destination vertex dest
 */
int Graph::dijkstra(Vertex *src, Vertex *dest) {

    // Step 1: Initialize distances from src to all other
    // vertices as UINT8_MAX INITE
    for (auto v: vertexSet) {
        v->setDist(UINT8_MAX);
        v->setPath(nullptr);
    }
    src->setDist(0);


    priority_queue<Vertex *, vector<Vertex *>, CompareVertex> priorityQueue;
    priorityQueue.push(src);

    while (!priorityQueue.empty()) {
        Vertex *current = priorityQueue.top();
        priorityQueue.pop();

        for (auto &e: current->getAdj()) {
            if (e->getFlow() < e->getCapacity()) {
                Vertex *neighbor = e->getDest();
                int new_dist = current->getDist() + e->getCapacity();
                if (new_dist < neighbor->getDist()) {
                    neighbor->setDist(new_dist);
                    priorityQueue.push(neighbor);
                    neighbor->setPath(e);
                }
            }
        }
    }

    return dest->getDist();
}

/**
 * This algorithm calculates the minimum residual capacity along a path from the source vertex to the target vertex in a given flow network.
 * Time Complexity: O(V)
 * @param s Vertex, source node
 * @param t Vertex, sink node
 * @return f int, represents the minimum residual capacity of the path from vertex source to vertex sink
 */
int findMinResidualAlongPath(Vertex *s, Vertex *t) {
    int f = UINT8_MAX;
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        //cout << v->getId() << " " <<  g->getStationHash()[v->getId()].getName() << " " << e->getCapacity() << " " << e->getCost() << endl;
        if (e->getDest() == v) {
            f = std::min(f, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

/**
 * This algorithm updates the flow along the augmentation path from the sink to the source.
 * Time Complexity: O(V)
 * @param s Vertex, represents the source node
 * @param t Vertex, represents the sink node
 * @param f int, represents the flow to be augmented
 */
void augmentFlowAlongPath(Vertex *s, Vertex *t, int f) {
    for (auto &v = t; v != s;) {
        auto *e = v->getPath();
        int flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        } else {
            //printf("oldssadsadsadsa");
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

// opção 6
/**
 * This algorithm calculates the maximum amount of trains that can simultaneously travel between two specific stations
 * with minimum cost for the company.
 * It implements Dijkstra's algorithm to find the shortest path between two nodes (the specific inserted stations), and
 * then uses that to calculate the maximum amount of flow between those nodes with minimum cost.
 * Time Complexity: O((E + V)logV + V)
 * @param source integer, represents the source node
 * @param target integer, represents the sink node
 * @return pair<int,int> cost_flow. The first item of the pair represents the minimum cost, and the second item represents the max flow.
 */
pair<int, int> Graph::maxTrainMinCost(int source, int target) {
    Vertex *s = findVertex(source);
    Vertex *t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw "Invalid source and/or target vertex";

    // Reset the flows
    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    // Loop to find augmentation paths
    //std::cout << "inicio" << std::endl;
    while (dijkstra(s, t) != UINT8_MAX) {
        //std::cout << "olaaa" << std::endl;

        int f = findMinResidualAlongPath(s, t);
        //std::cout << "flow" <<  f << std::endl;
        //print();
        augmentFlowAlongPath(s, t, f);
    }


    //int cost = calcularCusto();
    int cost = 0, maxFlow = 0;

    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            if (e->getFlow() > 0) {
                cost += e->getFlow() * e->getCost();
            }
            if (e->getDest() == t) {
                maxFlow += e->getFlow();
            }
        }
    }


    pair<int, int> cost_flow;
    cost_flow.first = cost;
    cost_flow.second = maxFlow;

    return cost_flow;
}


// opção 7
int maxTrain(Graph reduced_network, string const &orig, string const &dest) {
    return 0;
}

//opcao 8

void Graph::topkSegmentFailureAux(Graph g){
    for (auto v : vertexSet) {
        if(v->getIndegree() == -1){
            string stationName = g.getStationHash().at(v->getId()).getName();
            v->setIndegree(maxSimTrainStation(g, stationName));
        }
    }
}

void Graph::topkSegmentFailureDisable(Graph g){
    for (auto v : vertexSet) {
        string stationName = g.getStationHash().at(v->getId()).getName();
        v->setIndegreeUnavailable((maxSimTrainStation(g, stationName)));
    }
}

void Graph::disableEdge(Vertex *s, Vertex *t){
    for (auto v : vertexSet) {
        if(v==s){
            for (auto e: v->getAdj()) {
                if(e->getDest() == t){
                    e->setAvailable(false);
                }
            }
        }
    }

}


bool sortDisabledEdges(Vertex* v1, Vertex* v2){
    double affected1 = v1->getIndegreeUnavailable()/v1->getIndegree() * 100;
    double affected2 = v2->getIndegreeUnavailable()/v2->getIndegree() * 100;

    if(affected1 == affected2){
        return v1->getIndegreeUnavailable() > v2->getIndegreeUnavailable();
    }
    else{
        return affected1 > affected2;
    }
}

int topkSegmentFailure(Graph g){
    g.topkSegmentFailureAux(g);

//    disableEdge(src, sink);
    g.topkSegmentFailureDisable(g);

    std::sort(g.getVertexSet().begin(), g.getVertexSet().end(), sortDisabledEdges);

//    show top k impacted vertexes
}

void displayMenu() {
    static vector<string> options = {
            "1) Process dataset into database",
            "2) Calculate the maximum number of trains that can simultaneously travel between two specific stations",
            "3) Determine which stations require the most amount of trains when taking full advantage of the existing network capacity",
            "4) Report the top-k municipalities and districts, regarding their transportation needs",
            "5) Report the maximum number of trains that can simultaneously arrive at a given station, taking into consideration the entire railway grid",
            "6) Calculate the maximum amount of trains that can simultaneously travel between two specific stations with minimum cost for the company",
            "7) Calculate the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity",
            "8) Report the top-k stations most affected by each segment failure",
            "0) Quit"
    };

    cout << " <-----------------> Menu <-----------------> " << endl;
    for (string const &option: options) {
        cout << option << endl;
    }
    cout << "Insert option: ";
}

string getInput() {
    string input_string;
    std::getline(std::cin, input_string);
    return input_string;
}

int main() {
    Graph g = initGraph();

    int opt = 1;
    while (opt) {
        displayMenu();
        cin >> opt;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opt == 1) {
            g = initGraph();
        } else if (opt == 2) {
            if (g.empty()) g = initGraph();
            string orig, dest;
            cout << "Insert name of origin station: ";
            orig = getInput();
            cout << "Insert name of destiny station: ";
            dest = getInput();
            int origId = g.getInvertedHash()[orig];
            int destId = g.getInvertedHash()[dest];

            cout << g.maxFlowStations(origId, destId) << " trains can simultaneously travel between "
                 << orig << " and " << dest << endl;
        } else if (opt == 3) {
            if (g.empty()) g = initGraph();

            cout << "Please wait, this may take a few minutes..." << endl;
            solution3 result = largestCapPair(g);
            cout << "These stations require the most amount of trains when working at full capacity (" << result.maxFlow
                 << " trains):" << endl;
            for (auto station_pair: result.station_pairs) {
                cout << station_pair.front().getName() << " -> " << station_pair.back().getName() << endl;
            }

        } else if (opt == 4) {
            if (g.empty()) g = initGraph();
            int k;
            cout << "Insert k: ";
            cin >> k;
            topKMunDistr(g, k);
        } else if (opt == 5) {
            if (g.empty()) g = initGraph();
            string station_name;
            cout << "Insert station name: ";
            station_name = getInput();
            int num = maxSimTrainStation(g, station_name);
            cout << num << " trains can arrive at " << station_name << " simultaneously" << endl;
        } else if (opt == 6) {
            if (g.empty()) g = initGraph();
            string orig, dest;
            cout << "Insert origin station: ";
            orig = getInput();
            cout << "Insert destiny station: ";
            dest = getInput();

            // cout << "origin " << orig << endl;
            // cout << "dest " << dest << endl;

            int origId = g.getInvertedHash()[orig];
            int destId = g.getInvertedHash()[dest];

            // cout << "origin: " << origId << endl;
            // cout << "destiny: " << destId << endl;
            // cout << "aaaaa: " << g.getStationHash().find(destId)->second.getName() <<endl;

            pair<int, int> cost_flow = g.maxTrainMinCost(origId, destId);
            cout << "Numero de comboios em simultaneo (maxFlow): " << cost_flow.second << endl;
            cout << "Custo Minimo: " << cost_flow.first << endl;
        } else if (opt == 7) {
            if (g.empty()) g = initGraph();
            // obter estações para remover
            // removê-las do grafo
            string orig, dest;
            cout << "Insert origin station: ";
            cin >> orig;
            cout << "Insert destiny station: ";
            cin >> dest;
            //int num = maxTrainMinCost(g, orig, dest);
            cout << "do something with the output" << endl;
        } else if (opt == 8) {
            if (g.empty()) g = initGraph();
            bool flag = true;
            while(flag) {
                cout << "Select the unavailable edge by inserting two stations: " << endl;
                string orig, dest;
                cout << "Insert origin station: ";
                orig = getInput();
                cout << "Insert destiny station: ";
                dest = getInput();

                cout << "origin " << orig << endl;
                cout << "dest " << dest << endl;

                int origId = g.getInvertedHash()[orig];

                int destId = g.getInvertedHash()[dest];

                cout << "origin: " << origId << endl;
                cout << "destiny: " << destId << endl;

                Vertex* s = g.findVertex(origId);
                Vertex* t = g.findVertex(destId);

                g.disableEdge(s,t);

                cout << "If you want to turn another edge unavailable, insert the number 1: " << endl;
                int number;
                cin >> number;
                if(number != 1){
                    flag = false;
                }

            }


        } else if (opt == 0) {
            break;
        }
    }

    return 0;
}
