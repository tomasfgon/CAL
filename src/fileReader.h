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

    //template<class T>
    void readNodes_simples(Graph<VerticeInfo> &graph, string nome);

    //template<class T>
    void readEdges_simples(Graph<VerticeInfo> &graph, string nome);

    vector<int> readTags(Graph<VerticeInfo> &graph, string nome);


    vector<TipoLixo> generateTiposLixo();
};



