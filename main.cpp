#include <iostream>
#include "src/Graph.h"
#include "Menu.cpp"
#include "src/fileReader.cpp"

using namespace std;

int main()
{

    srand(time(NULL));
    cout << "CAL 2019/2020 - FEUP\n"
            "Tema 2 - WasteAPP\n\n"
            "Miguel Neves\nTomás Freitas Gonçalves\n\n\n";

    //TODO  loadMap();


    Graph<VerticeInfo> graph;
    FileReader fileReader;

    fileReader.readTags(graph, "maps/TagExamples/Porto/t02_tags_porto.txt");


    //Menu menu;


    return 0;
}
