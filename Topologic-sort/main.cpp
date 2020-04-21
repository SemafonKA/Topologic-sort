#include <iostream>
#include <fstream>
#include "Graph/Graph.h"

using namespace std;

int main(){
    system("chcp 65001"); system("cls");

    cout << "Making graph..." << endl << endl;
    Graph graph(6);
    cout << "Graph size is: " << graph.size() << endl << endl;
    graph.outList();
    cout << "\n*****************************************************\n\n";

    cout << "Make link from 2 to 3" << endl << endl;
    graph.makeLink(2, 3);
    graph.outList();
    cout << "\n*****************************************************\n\n";

    cout << "Make link from 5 to 2" << endl << endl;
    graph.makeLink(5, 2);
    graph.outList();
    cout << "\n*****************************************************\n\n";

    cout << "Make link from 1 to 3" << endl << endl;
    graph.makeLink(1, 3);
    graph.outList();
    cout << "\n*****************************************************\n\n";

    cout << "Remove element 3" << endl << endl;
    graph.removeElemenent(3);
    graph.outList();
    cout << "\n*****************************************************\n\n";

    cout << "Press enter to close";
    cin.get();
    return 0;
}
