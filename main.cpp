#include <iostream>
#include "src/Graph.h"
#include "Menu.cpp"
#include "src/fileReader.cpp"
#include <time.h>

using namespace std;

int main()
{

    srand(time(NULL));
    cout << "CAL 2019/2020 - FEUP\n"
            "Tema 2 - WasteAPP\n\n"
            "Miguel Neves\nTomás Freitas Gonçalves\n\n\n";

    //TODO  loadMap();

    Graph<VerticeInfo> graph;

    FileReader fileReader(graph);




    Menu menu(graph);


    return 0;
}
