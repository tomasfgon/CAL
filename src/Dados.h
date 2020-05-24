//
// Created by neves on 20/05/2020.
//

#pragma once



#include <vector>
#include "Coordenadas.h"
#include "Graph.h"
#include "TipoLixo.h"
#include <time.h>

using namespace std;

int idNumber;

class VerticeInfo {
public:

    VerticeInfo(Coordenadas &coordenadas) : coordenadas(coordenadas) {
        id = idNumber;
        idNumber++;
    }

    VerticeInfo(int id, Coordenadas &coordenadas) : coordenadas(coordenadas), id(id) {
    }


    bool static containsEnum(vector<TipoLixo> v, int value);

    vector<TipoLixo> static generateTiposLixo();


    friend std::ostream & operator <<(std::ostream &of, const VerticeInfo &ci);

    bool operator==(const VerticeInfo &ci);

    bool operator!=(const VerticeInfo &ci);

    VerticeInfo operator =(VerticeInfo verticeInfo);

private:

    int id;
    Coordenadas coordenadas;
public:
    Coordenadas &getCoordenadas();

    void setCoordenadas( Coordenadas &coordenadas);



};


bool VerticeInfo::containsEnum(vector<TipoLixo> v, int value){
    for(int i=0;i<v.size();i++){
        if (v[i] == value){
            return true;
        }
    }
    return false;
}

vector<TipoLixo> VerticeInfo::generateTiposLixo(){
    vector<TipoLixo> vet;
    srand(time(NULL));

    for(int i=0;i<rand()%5+1;i++){
        int random = rand()%6;
        TipoLixo tipoLixo = TipoLixo(random);
        if(!containsEnum(vet, random)){
            vet.push_back(tipoLixo);
        }
    }

    return vet;
}

std::ostream &operator<<(std::ostream &of, const VerticeInfo &ci) {
    of << "Vertice ID: " << ci.id;
    of << "  , Coordenadas: " << ci.coordenadas.getX() << " | " << ci.coordenadas.getY() << endl;
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

Coordenadas &VerticeInfo::getCoordenadas() {
    return coordenadas;
}

void VerticeInfo::setCoordenadas(Coordenadas &coordenadas) {
    VerticeInfo::coordenadas = coordenadas;
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
    PontoRecolhaDomiciliario(Coordenadas coordenadas, vector<TipoLixo> &tipoLixo) : VerticeInfo(
            coordenadas), tipoLixo(tipoLixo) {}

private:

    vector<TipoLixo>  tipoLixo;
    vector<double> pesos;
};//waste_basket

static double taxaViavel = 0.5;

class PontoRecolha : public VerticeInfo {
public:

    PontoRecolha(Coordenadas &coordenadas, vector<TipoLixo> &tipoLixo, vector<double> capMax) : VerticeInfo(coordenadas),
                                                                         tipoLixo(tipoLixo), capacidadesMax(capMax) {
        for(int i = 0; i < tipoLixo.size(); i++)
            taxasOcupacao.push_back(0);
    }


    const vector<double> &getCapacidadesMax() const {
        return capacidadesMax;
    }

    const vector<TipoLixo> &getTipoLixo() const {
        return tipoLixo;
    }

    const vector<double> &getTaxasOcupacao() const {
        return taxasOcupacao;
    }

private:

    vector<TipoLixo>  tipoLixo;
    vector<double> taxasOcupacao;
    vector<double> capacidadesMax;
}; //recycling

class PontoPartida : public VerticeInfo {
public:
    PontoPartida(Coordenadas coordenadas) : VerticeInfo(coordenadas) {}

};//waste_transfer_station

class CentroReciclagem : public VerticeInfo {
public:
    CentroReciclagem(Coordenadas coordenadas, TipoLixo tipoLixo) : VerticeInfo(coordenadas), tipoLixo(tipoLixo) {}

private:

    TipoLixo tipoLixo;
};//waste_disposal

static double capcidadeMaxCamiao = 500; //valor possivel de ser mudado para fazer os testes


class Camiao {
public:
    Camiao(TipoLixo tipoLixo) : tipoLixo(tipoLixo) {}

    TipoLixo getTipoLixo() const {
        return tipoLixo;
    }

private:
    TipoLixo tipoLixo;
    double capacidadeAtual = 0;

};



//Dados Saida

class SequenciaIdeal {
public:
    SequenciaIdeal(vector<Edge<VerticeInfo>> &arestasIdeais) : arestasIdeais(arestasIdeais) {}

private:

    vector<Edge<VerticeInfo>> arestasIdeais;
};


//waste_basket
//recycling
//waste_disposal
//waste_transfer_station