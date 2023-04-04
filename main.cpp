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
            double residual = e->getWeight() - e->getFlow();
            if (! w->isVisited() && residual > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
        for(auto e: v->getIncoming()) {
            auto w = e->getOrig();
            double residual = e->getFlow();
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
    double res;
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
        double f = INF;
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
            double flow = e->getFlow();
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

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm.  The
// function also detects negative weight cycle
int Graph::bellmanFordAlgorithm(Graph graph, int src, int dest)
{
    int V = graph.getNumVertex();
    int dist[V];

    // Step 1: Initialize distances from src to all other
    // vertices as INFINITE
    for(auto v : vertexSet) {
        int i = v->getId();
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple
    // shortest path from src to any other vertex can have
    // at-most |V| - 1 edges
    for(auto v : vertexSet) {
        for(auto e: v->getAdj()) {
            Vertex* vertexU = e->getOrig();
            Vertex* vertexV = e->getDest();
            int u = vertexU->getId();
            int v = vertexV->getId();

            if (dist[u] != INT_MAX && dist[u] + e->getCusto() < dist[v])
                dist[v] = dist[u] + e->getCusto();
        }
    }

    return dist[dest];

}

double findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
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

void augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
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

int Graph::calcularCusto(){
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            if(e->getFlow() > 0){

            }
        }
    }
}

// opção 6
int Graph::maxTrainMinCost(Graph network, int source, int target) {
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
    int custo;
    // Loop to find augmentation paths
    while(bellmanFordAlgorithm(network, source, target) != INT_MAX) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }

    int cost = calcularCusto(network)

    return maxFlow;
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
    getline(cin, input_string);
    return input_string;
}

int main() {
    Graph g;

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
            cin >> orig;
            cout << "Insert destiny station: ";
            cin >> dest;
            int num = maxTrainMinCost(g, orig, dest);
            cout << "do something with the output" << endl;
        } else if (opt == 7) {
            if (g.empty()) g = initGraph();
            // obter estações para remover
            // removê-las do grafo
            string orig, dest;
            cout << "Insert origin station: ";
            cin >> orig;
            cout << "Insert destiny station: ";
            cin >> dest;
            int num = maxTrainMinCost(g, orig, dest);
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
