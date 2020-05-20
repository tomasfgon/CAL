//
// Created by neves on 20/05/2020.
//

#ifndef PROJETO_TRANSPORTEUE_H
#define PROJETO_TRANSPORTEUE_H

#endif //PROJETO_TRANSPORTEUE_H

#include <vector>
#include "Coordenadas.h"
#include "Graph.h"

using namespace std;

class VerticeInfo {
    int id;
    Coordenadas coordenadas;
};

//Dados Entrada

class TransporteUE {

    TipoLixo tipoLixo;
    double pesoMin;
    double pesoMax;
};

class DepositoUP {

    TipoLixo tipoLixo;
    double peso;
};



class PontoRecolhaDomiciliario : VerticeInfo{

    vector<TipoLixo>  tipoLixo;
    vector<double> pesos;
};

class PontoRecolha : VerticeInfo {

    vector<TipoLixo>  tipoLixo;
    vector<double> taxasOcupacao;
    vector<double> capacidadesMax;
};

class PontoPartida : VerticeInfo {

};

class CentroReciclagem : VerticeInfo {

    TipoLixo tipoLixo;
};

class Camiao {

    TipoLixo tipoLixo;
    double capacidadeAtual;
    double capcidadeMax;

};


//Dados Saida

class SequenciaIdeal {

    vector<Edge<VerticeInfo>> arestasIdeais;
};