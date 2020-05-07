#include <iostream>
#include <fstream>
#include "Graph/Graph.h"
#include <fstream>

using namespace std;

const string inputFile = "IO files/input.txt";
const string outputFile = "IO files/output.txt";

namespace n_Graph{
void getFromFile(const string& _adress, Graph& _to) {
    ifstream ifile(_adress);
    int size, amountOfCommands;
    ifile >> size >> amountOfCommands;
    _to.makeGraph(size);
    int from, to;
    for (size_t i = 0; i < amountOfCommands; i++) {
        ifile >> from >> to;
        _to.makeLink(from, to);
    }
    ifile.close();
}

void putToFile(const string& _adress, const pair<int, Dlist<int>>& _subgraphs) {
    ofstream ofile(_adress, ios::trunc | ios::out);
    ofile << _subgraphs.first << endl;
    const Dlist<int>& keys = _subgraphs.second;
    for (int i = 0; i < keys.size(); ++i) {
        ofile << keys.at(i) << " ";
    }
    ofile.close();
}
} // namespace n_Graph

int main(){
    system("chcp 65001"); system("cls");

    cout << "Reading and making graph... \n\n";
    Graph graph;
    n_Graph::getFromFile(inputFile, graph);
    graph.outList();

    cout << "Getting subgraphs... \n\n";
    pair<int, Dlist<int>> subgraphs;
    subgraphs = graph.subgraphs();

    cout << "Writing results in output.txt file... \n\n";
    n_Graph::putToFile(outputFile, subgraphs);

    cout << "\nPress enter to close";
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
    return 0;
}
