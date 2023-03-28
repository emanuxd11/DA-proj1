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

// opção 6 e 7
int maxTrainMinCost(Graph network, string const &orig, string const &dest) {
    return 0;
}

void displayMenu() {
    static vector<string> options = {
            "1) Processamento de dados",
            "2) Calcular o número máximo de comboios que podem circular em simultâneo entre duas estações",
            "3) Determinar o(s) par(es) de estações que requer(em) maior número de comboios para usar toda a capacidade das linhas",
            "4) Determinar os k municípios e distritos com maior utilização das linhas ferroviárias",
            "5) Determinar numero máximo de comboios que podem chegar simultaneamente a uma dada estação",
            "6) Calcular o número máximo de comboios que podem viajar simultaneamente entre duas dadas estações com custo mínimo",
            "7) Calcular o número máxomp de comboios que podem viajar simultaneamente entre duas estações numa rede de conectividade reduzida",
            "8) Relatório das k estações mais afetadas por cada falha de segmento",
            "9) Sair"
    };

    cout << " <-----------------> Menu <-----------------> " << endl;
    for (string const &option : options) {
        cout << option << endl;
    }
    cout << "Insira uma opção: " << endl;
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
            cout << "Insira estação de origem: ";
            cin >> orig;
            cout << "Insira estação de destino: ";
            cin >> dest;
            g = maxTrainFlow(g, orig, dest);
            cout << "fazer qlqr cena com o output" << endl;
        } else if (opt == 3) {
            if (g.empty()) g = initGraph();
            auto stations = largestCapPair(g);
            cout << "fazer qlqr cena com o output" << endl;
        } else if (opt == 4) {
            if (g.empty()) g = initGraph();
            int k;
            cout << "Insira k: ";
            cin >> k;
            auto output = topKMunDistr(g);
            cout << "fazer qlqr cena com o output" << endl;
        } else if (opt == 5) {
            if (g.empty()) g = initGraph();
            string station_name;
            cout << "Insira a estação: ";
            cin >> station_name;
            int num = maxSimTrainStation(g, station_name);
            cout << "fazer qlqr cena com o output" << endl;
        } else if (opt == 6) {
            if (g.empty()) g = initGraph();
            string orig, dest;
            cout << "Insira estação de origem: ";
            cin >> orig;
            cout << "Insira estação de destino: ";
            cin >> dest;
            int num = maxTrainMinCost(g, orig, dest);
            cout << "fazer qlqr cena com o output" << endl;
        } else if (opt == 7) {
            if (g.empty()) g = initGraph();
            // obter estações para remover
            // removê-las do grafo
            string orig, dest;
            cout << "Insira estação de origem: ";
            cin >> orig;
            cout << "Insira estação de destino: ";
            cin >> dest;
            int num = maxTrainMinCost(g, orig, dest);
            cout << "fazer qlqr cena com o output" << endl;
        } else if (opt == 8) {
            if (g.empty()) g = initGraph();
            // ?
        } else if (opt == 9) {
            break;
        }
    }

    return 0;
}
