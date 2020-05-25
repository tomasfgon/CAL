#include <iostream>
#include "src/Graph.h"
#include "Menu.cpp"

#include <time.h>



using namespace std;

int main()
{

    srand(time(NULL));
    cout << "CAL 2019/2020 - FEUP\n"
            "Tema 2 - WasteAPP\n\n"
            "Miguel Neves\nTomás Freitas Gonçalves\n\n\n";

    //TODO  loadMap();



/*

    Coordenadas c1(0,2);
    Coordenadas c2(3,0);
    Coordenadas c3(-1,1);
    Coordenadas c4(2,2);

    VerticeInfo *v1 = new VerticeInfo(c1,1);
    VerticeInfo *v2 = new VerticeInfo(c2,2);
    VerticeInfo *v3 = new VerticeInfo(c3,3);
    VerticeInfo *v4 = new VerticeInfo(c4,4);

    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    graph.addVertex(v4);
*/




/*    PrintGraph printGraph;
    printGraph.create(graph);*/

    //FileReader fileReader(graph);

    //printGraph.create(graph);


    Graph<VerticeInfo> graph;
    Menu menu(graph);



    return 0;
}
