//
// Created by Tomas Goncalves on 24/05/2020.
//

#ifndef PROJETO_PRINTGRAPH_H
#define PROJETO_PRINTGRAPH_H

#include "../lib/graphviewer.h"
#include "../src/Dados.h"



class PrintGraph {

public:

    static string image;


    GraphViewer* useCase3(Graph<VerticeInfo> &g, VerticeInfo pontoAtual, TipoLixo tipoLixo);

    GraphViewer* create(Graph<VerticeInfo> &g);


};

#endif //PROJETO_PRINTGRAPH_H
