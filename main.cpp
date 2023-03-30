#include <iostream>
#include <unordered_map>
#include "includes/Graph.h"
#include "includes/Database.h"
#include "includes/Station.h"

using namespace std;

// opção 1
Graph initGraph() {
    return Database::loadGraph();
}

// opção 2
// auxiliar
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
vector<vector<Station>> largestCapPair(Graph network) {
    vector<vector<Station>> res;
    unordered_map<int, Station> stations = network.getStationHash();
    int largest = -1;

    for (int i = 0; i < network.getVertexSet().size(); i++) {
        for (int j = i + 1; j < network.getVertexSet().size(); j++) {
            auto v = network.findVertex(i);
            auto u = network.findVertex(j);
            if (u == v) continue;
            int flow = network.maxFlowStations(v->getId(), u->getId());
            if (flow == largest) {
                vector<Station> current = { stations[v->getId()], stations[u->getId()] };
                res.push_back(current);
            } else if (flow > largest) {
                res.clear();
                vector<Station> current = { stations[v->getId()], stations[u->getId()] };
                res.push_back(current);
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

// opção 6
int maxTrainMinCost(Graph network, string const &orig, string const &dest) {
    return 0;
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

            cout << "result: " << g.maxFlowStations(origId, destId) << endl;
        } else if (opt == 3) {
            if (g.empty()) g = initGraph();
            auto stations = largestCapPair(g);
            cout << "do something with the output" << endl;
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
