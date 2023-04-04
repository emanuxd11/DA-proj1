#include <iostream>
#include <unordered_map>
#include "includes/Graph.h"
#include "includes/VertexEdge.h"
#include "includes/Database.h"
#include "includes/Station.h"

using namespace std;

// opção 1
Graph initGraph() {
    return Database::loadGraph();
}

// opção 2
bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while(!q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            auto w = e->getDest();
            int residual = e->getWeight() - e->getFlow();
            if (! w->isVisited() && residual > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
        for(auto e: v->getIncoming()) {
            auto w = e->getOrig();
            int residual = e->getFlow();
            if (! w->isVisited() && residual > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }
    return t->isVisited();
}

int Graph::maxFlowStations(int source, int target) {
    int res;
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);

    if (s == nullptr || t == nullptr || s == t) {
        throw std::logic_error("Invalid source and/or target vertex");
    }

    // Reset the flows
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    // Loop to find augmentation paths
    while (findAugmentingPath(s, t)) {
        int f = UINT8_MAX;
        for (auto v = t; v != s; ) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                f = std::min(f, e->getWeight() - e->getFlow());
                v = e->getOrig();
            }
            else {
                f = std::min(f, e->getFlow());
                v = e->getDest();
            }
        }
        for (auto v = t; v != s; ) {
            auto e = v->getPath();
            int flow = e->getFlow();
            if (e->getDest() == v) {
                e->setFlow(flow + f);
                v = e->getOrig();
            }
            else {
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
                res.station_pairs.push_back({ stations[i], stations[j] });
            } else if (flow > res.maxFlow) {
                res.station_pairs.erase(res.station_pairs.begin(), res.station_pairs.end());
                res.station_pairs.push_back({ stations[i], stations[j] });
                res.maxFlow = flow;
            }
        }
    }

    return res;
}

// opção 4
vector<string> topKMunDistr(Graph network) {
    return vector<string>();
}

// opção 5
int maxSimTrainStation(Graph network, string const &station_name) {
    return 0;
}

struct CompareVertex {
    bool operator()(Vertex* v1, Vertex* v2) {
        return v1->getDist() > v2->getDist();
    }
};

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm.  The
// function also detects negative weight cycle
int Graph::dijkstra(Vertex* src, Vertex* dest) {

    // Step 1: Initialize distances from src to all other
    // vertices as UINT8_MAX INITE
    for(auto v : vertexSet) {
        v->setDist(UINT8_MAX);
        v->setPath(nullptr);
    }
    src->setDist(0);


    priority_queue<Vertex*, vector<Vertex*>, CompareVertex> priorityQueue;
    priorityQueue.push(src);

    while(!priorityQueue.empty()){
        Vertex* current = priorityQueue.top();
        priorityQueue.pop();

        for(auto& e : current->getAdj()){
            if(e->getFlow() < e->getWeight()){
                Vertex* neighbor = e->getDest();
                int new_dist = current->getDist() + e->getWeight();
                if(new_dist < neighbor->getDist()){
                    neighbor->setDist(new_dist);
                    priorityQueue.push(neighbor);
                    neighbor->setPath(e);
                }
            }
        }
    }

    return dest->getDist();

}

int findMinResidualAlongPath(Vertex *s, Vertex *t) {
    int f = UINT8_MAX;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void augmentFlowAlongPath(Vertex *s, Vertex *t, int f) {
    for (auto& v = t; v != s; ) {
        auto* e = v->getPath();
        int flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

// opção 6
pair <int, int> Graph::maxTrainMinCost(int source, int target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw "Invalid source and/or target vertex";

    // Reset the flows
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    // Loop to find augmentation paths
    while(dijkstra(s, t) != UINT8_MAX) {
        int f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }


    //int cost = calcularCusto();
    int cost = 0, maxFlow = 0;

    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            if(e->getFlow() > 0){
                cost += e->getFlow()*e->getCusto();
            }
            if(e->getDest() == t){
                maxFlow += e->getFlow();
            }
        }
    }



    pair <int, int> cost_flow;
    cost_flow.first = cost;
    cost_flow.second = maxFlow;

    return cost_flow;
}



// opção 7
int maxTrain(Graph reduced_network, string const &orig, string const &dest) {
    return 0;
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
            "9) Quit"
    };

    cout << " <-----------------> Menu <-----------------> " << endl;
    for (string const &option : options) {
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

            cout << "origin: " << origId << endl;
            cout << "destiny: " << destId << endl;

            cout << "result: " << g.maxFlowStations(origId, destId) << endl;
        } else if (opt == 3) {
            if (g.empty()) g = initGraph();

            cout << "Please wait, this may take a few minutes..." << endl;
            solution3 result = largestCapPair(g);
            cout << "These stations require the most amount of trains when working at full capacity (" << result.maxFlow << " trains)" << endl;
            for (auto station_pair : result.station_pairs) {
                cout << station_pair.front().getName() << " -> " << station_pair.back().getName() << endl;
            }

        } else if (opt == 4) {
            if (g.empty()) g = initGraph();
            int k;
            cout << "Insert k: ";
            cin >> k;
            auto output = topKMunDistr(g);
            cout << "do something with the output" << endl;
        } else if (opt == 5) {
            if (g.empty()) g = initGraph();
            string station_name;
            cout << "Insert station name: ";
            cin >> station_name;
            int num = maxSimTrainStation(g, station_name);
            cout << "do something with the output" << endl;
        } else if (opt == 6) {
            if (g.empty()) g = initGraph();
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
            cout << "aaaaa: " << g.getStationHash().find(destId)->second.getName() <<endl;

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
            // ?
        } else if (opt == 9) {
            break;
        }
    }

    return 0;
}
