//
// Created by neves on 21/05/2020.
//

#pragma once


#include "Dados.h"
#include <utility>

class UseCases {
public:

    bool checkConectividade(Graph<VerticeInfo> graph, Vertex<VerticeInfo> v); //UC nao existente por agora
    bool checkConectividade2Points(Graph<VerticeInfo> graph, Vertex<VerticeInfo> vInicial, Vertex<VerticeInfo> vFinal); //UC nao existente por agora

    bool addPontoRecolha(PontoRecolha &pontoRecolha, Graph<VerticeInfo> &graph); //UC2

    bool addRecolhaDomestica(PontoRecolhaDomiciliario &pontoRecolhaDomiciliario, Graph<VerticeInfo> graph); //UC5

    vector<vector<VerticeInfo>> determinarRotaCamioes(PontoPartida pontoPartida, CentroReciclagem centroReciclagem, Graph<VerticeInfo> graph); //UC3

    vector<PontoRecolha> getAllPontosRecolha(Graph<VerticeInfo> graph);

    vector<PontoRecolhaDomiciliario> getAllPontosRecolhaDomestica(Graph<VerticeInfo> graph);

    bool checkConectividadeDomiciliario(Graph<VerticeInfo> graph, Vertex<VerticeInfo> v);

    vector<Edge<VerticeInfo>> getEdgesFromVertexes(vector<VerticeInfo> verticeInfos,vector<VerticeInfo> pontosRecolha ,Graph<VerticeInfo> graph);

private:

    vector<PontoRecolha> getPontosAcimaTaxaViavel(Graph<VerticeInfo> graph);

    vector<pair<double,TipoLixo>> calcularLixoTotalPorTipo(vector<PontoRecolha> pontosRecolha);

    vector<Camiao> calcularCamioesNecessarios(vector<PontoRecolha> pontosRecolha);

    vector<vector<VerticeInfo>> minimizarDistPercorrida(Graph<VerticeInfo> &graph, vector<Camiao> camioesNecessarios, vector<PontoRecolha> pontosRecolha, PontoPartida pontoPartida, CentroReciclagem centroReciclagem);

    void obterPontosRecolhaMaisProximo(vector<PontoRecolha> pontosRecolha, VerticeInfo oldPonto, int tipoLixoAtual, Graph<VerticeInfo> graph, vector<VerticeInfo> &listToReturn);
};


