//
// Created by Tomas Goncalves on 21/05/2020.
//


#include "fileReader.h"


using namespace std;

//mapas
//template <class T>
void FileReader::readNodes_simples(Graph<VerticeInfo> &graph, string nome) {
    int numberNodes;
    string line;


    string filename = nome;
    ifstream file;

    file.open(filename);

    getline(file, line);

    numberNodes = stoi(line);

    for(int i=0;i<numberNodes;i++){
        double x,y; int id;
        unsigned sep;

        getline(file, line);

        sep = line.find(',');
        //cout << line.substr(1,sep) << endl;
        id = stoi(line.substr(1,sep));
        line.erase(0,sep+1);


        sep = line.find(',');

        x = stod(line.substr(0,sep));
        line.erase(0,sep+1);
        //cout << "x: " << x << endl;

        sep = line.find(')');
        y = stod(line.substr(0,sep));
        //cout << "y: "<<y <<endl << endl;



        Coordenadas coordenadas(x,y);
        VerticeInfo info(id, coordenadas);
        graph.addVertex(info);
    }
    file.close();
}

//template <class T>
void FileReader::readEdges_simples(Graph<VerticeInfo> &graph, string nome){
    int numberEdges;
    ifstream file;
    string line;
    string filename = nome;

    file.open(filename);


    getline(file, line);
    //cout << "number: " << line << endl;
    numberEdges = stoi(line);

    for(int i=0;i<numberEdges;i++){
        int id1,id2;
        unsigned sep;
        getline(file, line);
        sep = line.find(",");
        id1 = stoi(line.substr(1, sep));
        //cout << "id1: " << id1 << endl;
        line.erase(0,sep+1);
        sep = line.find(')');
        id2 = stoi(line.substr(0, sep));
        //cout << "id2: " << id2 << endl << endl;


        Coordenadas coordenadas(0,0);
        VerticeInfo vi1(id1, coordenadas);
        VerticeInfo vi2(id2, coordenadas);


        Vertex<VerticeInfo> *v1 = graph.findVertex(vi1);
        Vertex<VerticeInfo> *v2 = graph.findVertex(vi2);




        double x1 = v1->getInfo().getCoordenadas().getX();
        double y1 = v1->getInfo().getCoordenadas().getY();
        double x2 = v2->getInfo().getCoordenadas().getX();
        double y2 = v2->getInfo().getCoordenadas().getY();



        double distance = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
        //cout << "distance: "<<distance << endl;



        graph.addEdge(v1->getInfo(),v2->getInfo(), distance);


    }

    file.close();

}
