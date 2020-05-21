//
// Created by neves on 21/05/2020.
//

#include "UseCases.h"

bool UseCases::addPontoRecolha(PontoRecolha &pontoRecolha, Graph<VerticeInfo> &graph) {

    //Verificar conectividade
    Graph<VerticeInfo> graphCopy = graph;
    graphCopy.addVertex(pontoRecolha);
    if(checkConectividade(graphCopy)){
        graph.addVertex(pontoRecolha);
        return true;
    }

return false;
}

bool UseCases::checkConectividade(Graph<VerticeInfo> graph) { //usando dfs



    vector<VerticeInfo> verticesOrdenado = graph.dfs();
    vector<Vertex< VerticeInfo> *> verticesTotais = graph.getVertexSet();


    for(int i = 0; i < graph.getNumVertex(); i++){
        if(!verticesTotais.at(i)->isVisited()){
            return false;
        }
    }

  //para o grafo transposto

    return true;
}
