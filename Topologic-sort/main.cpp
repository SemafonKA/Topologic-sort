#include <iostream>
#include <fstream>
#include "Graph/Graph.h"
#include "Graph/Topological_sort.h"
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

void putToFile(const string& _adress, const Dlist<int>& _graph) {
    ofstream ofile(_adress, ios::trunc | ios::out);
    if (_graph.size() == 0) ofile << -1;
    else 
        for (size_t i = 0; i < _graph.size(); i++) {
            ofile << _graph.at(i) << " ";
        }
    ofile.close();
}
} // namespace File

int main(){
    system("chcp 65001"); system("cls");

    cout << "Reading and making graph..." << endl << endl;
    Graph graph;
    n_Graph::getFromFile(inputFile, graph);
    graph.outList();

    cout << "Making topoligical sort for graph..." << endl << endl;
    Dlist<int> sorted = Topological_sort::forGraph(graph);

    cout << "Writing results in output.txt file... ";
    n_Graph::putToFile(outputFile, sorted);

    cout << "\nPress enter to close";
    cin.get();
    return 0;
}
