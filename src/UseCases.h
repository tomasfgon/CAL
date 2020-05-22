//
// Created by neves on 21/05/2020.
//

#ifndef PROJETO_USECASES_H
#define PROJETO_USECASES_H


#include "Dados.h"
#include <utility>

class UseCases {
public:

    bool checkConectividade(Graph<VerticeInfo> graph); //UC nao existente por agora

    bool addPontoRecolha(PontoRecolha &pontoRecolha, Graph<VerticeInfo> &graph); //UC2

    bool addRecolhaDomestica(PontoRecolhaDomiciliario &pontoRecolhaDomiciliario, Graph<VerticeInfo> graph); //UC5

    Edge<VerticeInfo> determinarRotaCamioes(PontoPartida pontoPartida, CentroReciclagem centroReciclagem, Graph<VerticeInfo> graph); //UC3

private:

    vector<PontoRecolha> getPontosAcimaTaxaViavel(Graph<VerticeInfo> graph);

    vector<pair<double,TipoLixo>> calcularLixoTotalPorTipo(vector<PontoRecolha> pontosRecolha);

    vector<Camiao> calcularCamioesNecessarios(vector<PontoRecolha> pontosRecolha);

    vector<Edge<VerticeInfo>> minimizarDistPercorrida(Graph<VerticeInfo> &graph, vector<Camiao> camioesNecessarios, vector<PontoRecolha> pontosRecolha);
};


#endif //PROJETO_USECASES_H
