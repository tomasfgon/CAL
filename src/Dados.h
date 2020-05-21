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

int idNumber;

class VerticeInfo {
public:

    VerticeInfo(Coordenadas &coordenadas) : coordenadas(coordenadas) {
        id = idNumber;
        idNumber++;
    }

    friend std::ostream & operator <<(std::ostream &of, const VerticeInfo &ci);

    bool operator==(const VerticeInfo &ci);

    bool operator!=(const VerticeInfo &ci);

    VerticeInfo operator =(VerticeInfo verticeInfo);

private:

    int id;
    Coordenadas coordenadas;


};

std::ostream &operator<<(std::ostream &of, const VerticeInfo &ci) {
    of << "Vertice ID: " << ci.id;
    of << "  , Coordenadas: " << ci.coordenadas.latitude << " | " << ci.coordenadas.longitude << endl;
    return of;
}

bool VerticeInfo::operator==(const VerticeInfo &ci) {
    return id == ci.id;

}

bool VerticeInfo::operator!=(const VerticeInfo &ci) {
    return id != ci.id;
}

VerticeInfo VerticeInfo::operator=(VerticeInfo verticeInfo2) {
    return VerticeInfo(verticeInfo2.coordenadas);
}


//Dados Entrada

class TransporteUE {

public:
    TransporteUE(TipoLixo &tipoLixo1, double &pesoMin1, double &pesoMax1) : tipoLixo(tipoLixo1), pesoMin(pesoMin1), pesoMax(pesoMax1) {}

private:
    TipoLixo tipoLixo;
    double pesoMin;
    double pesoMax;


};


class DepositoUP {

public:
    DepositoUP(TipoLixo &tipoLixo1, double &peso1) : tipoLixo(tipoLixo1), peso(peso1) {}
private:
    TipoLixo tipoLixo;
    double peso;


};



class PontoRecolhaDomiciliario : public VerticeInfo{

public:
    PontoRecolhaDomiciliario(Coordenadas &coordenadas, vector<TipoLixo> &tipoLixo) : VerticeInfo(
            coordenadas), tipoLixo(tipoLixo) {}

private:

    vector<TipoLixo>  tipoLixo;
    vector<double> pesos;
};



class PontoRecolha : public VerticeInfo {
public:
    PontoRecolha(Coordenadas &coordenadas, vector<TipoLixo> &tipoLixo) : VerticeInfo(coordenadas),
                                                                         tipoLixo(tipoLixo) {}

private:

    vector<TipoLixo>  tipoLixo;
    vector<double> taxasOcupacao;
    vector<double> capacidadesMax;
};

class PontoPartida : public VerticeInfo {
public:
    PontoPartida(Coordenadas &coordenadas) : VerticeInfo(coordenadas) {}

};

class CentroReciclagem : public VerticeInfo {
public:
    CentroReciclagem(Coordenadas &coordenadas, TipoLixo tipoLixo) : VerticeInfo(coordenadas), tipoLixo(tipoLixo) {}

private:

    TipoLixo tipoLixo;
};

class Camiao {
public:
    Camiao(TipoLixo tipoLixo) : tipoLixo(tipoLixo) {}

private:

    TipoLixo tipoLixo;
    double capacidadeAtual;
    double capcidadeMax;

};


//Dados Saida

class SequenciaIdeal {
public:
    SequenciaIdeal(vector<Edge<VerticeInfo>> &arestasIdeais) : arestasIdeais(arestasIdeais) {}

private:

    vector<Edge<VerticeInfo>> arestasIdeais;
};