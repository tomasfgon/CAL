#include <iostream>
#include "src/Graph.h"
#include "Menu.cpp"
#include "src/fileReader.cpp"

using namespace std;

int main()
{

    cout << "CAL 2019/2020 - FEUP\n"
            "Tema 2 - WasteAPP\n\n"
            "Miguel Neves\nTomás Freitas\nAbel Tiago\n\n\n";

    //TODO  loadMap();


    Graph<VerticeInfo> graph;
    FileReader fileReader;


    fileReader.readNodes_simples(graph,"maps/GridGraphs/4x4/nodes.txt");
    fileReader.readEdges_simples(graph,"maps/GridGraphs/4x4/edges.txt");


    Menu menu(graph);


    return 0;
}
