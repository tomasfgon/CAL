//
// Created by Tomas Goncalves on 21/05/2020.
//

#pragma once
#include "Dados.h"
#include <string>
#include <fstream>
#include <math.h>

class FileReader {


public:

    FileReader();


    //template<class T>
    bool readNodes_simples(Graph<VerticeInfo> &graph, string nome);

    //template<class T>
    bool readEdges_simples(Graph<VerticeInfo> &graph, string nome);

    bool readTags(Graph<VerticeInfo> &graph, string nome);



};



