//
// Created by neves on 21/05/2020.
//

#ifndef PROJETO_USECASES_H
#define PROJETO_USECASES_H


#include "Dados.h"

class UseCases {
public:

    bool checkConectividade(Graph<VerticeInfo> graph); //UC nao existente por agora

    bool addPontoRecolha(PontoRecolha &pontoRecolha, Graph<VerticeInfo> &graph); //UC2

    bool addRecolhaDomestica(PontoRecolhaDomiciliario &pontoRecolhaDomiciliario, Graph<VerticeInfo> graph); //UC5

    Edge<VerticeInfo> determinarRotaCamioes(PontoPartida pontoPartida, CentroReciclagem centroReciclagem, Graph<VerticeInfo> graph); //UC3

private:

    vector<VerticeInfo> getPontosAcimaTaxaViavel(Graph<VerticeInfo> graph);

    vector<Camiao> calcularCamioesNecessarios(vector<VerticeInfo> pontosRecolha);
};


#endif //PROJETO_USECASES_H
