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

// opção 2, ver 7 da TP3
Graph maxTrainFlow(Graph network, string const &source, string const &dest) {
    return network;
}

// opção 3
vector<Station> largestCapPair(Graph network) {
    return vector<Station>();
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

int main() {
    Graph g;

    int opt = 0;
    while (true) {
        displayMenu();
        cin >> opt;

        if (opt == 1) {
            g = initGraph();
        } else if (opt == 2) {
            if (g.empty()) g = initGraph();
            string orig, dest;
            cout << "Insert name of origin station: ";
            cin >> orig;
            cout << "Insert name of destiny station: ";
            cin >> dest;
            g = maxTrainFlow(g, orig, dest);
            cout << "do something with the output" << endl;
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
