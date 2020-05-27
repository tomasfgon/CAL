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



class VerticeInfo {
public:


    VerticeInfo(Coordenadas &coordenadas, int id) : coordenadas(coordenadas), id(id) {
    }

    virtual ~VerticeInfo() = default;



    bool static containsEnum(vector<TipoLixo> v, int value);

    vector<TipoLixo> static generateTiposLixo();


    friend std::ostream & operator <<(std::ostream &of, const VerticeInfo &ci);

    bool operator==(const VerticeInfo &ci);
    bool operator==(const int &ci);

    bool operator!=(const VerticeInfo &ci);



    Coordenadas &getCoordenadas();

    void setCoordenadas( Coordenadas &coordenadas);

    int getId() const;

private:

    int id;
    Coordenadas coordenadas;




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


Coordenadas &VerticeInfo::getCoordenadas() {
    return coordenadas;
}

void VerticeInfo::setCoordenadas(Coordenadas &coordenadas) {
    VerticeInfo::coordenadas = coordenadas;
}

int VerticeInfo::getId() const {
    return id;
}

bool VerticeInfo::operator==(const int &ci) {
    return id == ci;
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



class PontoRecolhaDomiciliario : public virtual VerticeInfo{

public:
    PontoRecolhaDomiciliario(Coordenadas coordenadas, vector<TipoLixo> &tipoLixo, vector<double> capMax, int id) :VerticeInfo(coordenadas,
                                                                                                                              id),
                                                                                                                  tipoLixo(tipoLixo), capacidadesMax(capMax) {}

    const vector<double> &getCapacidadesMax() const {
        return capacidadesMax;
    }

    const vector<TipoLixo> &getTipoLixo() const {
        return tipoLixo;
    }

    const vector<double> &getTaxasOcupacao() const {
        return taxasOcupacao;
    }

    void setTaxasOcupacao(const vector<double> &taxasOcupacao) {
        PontoRecolhaDomiciliario::taxasOcupacao = taxasOcupacao;
    }
private:

    vector<TipoLixo>  tipoLixo;
    vector<double> taxasOcupacao;
    vector<double> capacidadesMax;
};//waste_basket

static double taxaViavel = 0.5;

class PontoRecolha : public virtual VerticeInfo {
public:

    PontoRecolha(Coordenadas &coordenadas, vector<TipoLixo> &tipoLixo, vector<double> capMax, int id)
            : VerticeInfo(coordenadas,
                          id),
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

    void setTaxasOcupacao(const vector<double> &taxasOcupacao) {
        PontoRecolha::taxasOcupacao = taxasOcupacao;
    }

private:

    vector<TipoLixo>  tipoLixo;
    vector<double> taxasOcupacao;
    vector<double> capacidadesMax;
}; //recycling

class PontoPartida : public virtual VerticeInfo {
public:
    PontoPartida(Coordenadas coordenadas, int id) : VerticeInfo(coordenadas, id) {}

};//waste_transfer_station


class CentroReciclagem : public virtual VerticeInfo {
public:
    CentroReciclagem(Coordenadas coordenadas, int id) : VerticeInfo(coordenadas, id) {}

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


//waste_basket
//recycling
//waste_disposal
//waste_transfer_station


double getMaxX(Graph<VerticeInfo> &g){
    double value = g.getVertexSet()[0]->getInfo()->getCoordenadas().getX();
    for(auto i: g.getVertexSet()){
        if(i->getInfo()->getCoordenadas().getX()>value){
            value = i->getInfo()->getCoordenadas().getX();
        }

    }
    return value;
}

double getMaxY(Graph<VerticeInfo> &g){
    double value = g.getVertexSet()[0]->getInfo()->getCoordenadas().getY();
    for(auto i: g.getVertexSet()){
        if(i->getInfo()->getCoordenadas().getY()>value){
            value = i->getInfo()->getCoordenadas().getY();
        }

    }
    return value;

}

double getMinX(Graph<VerticeInfo> &g){
    double value = g.getVertexSet()[0]->getInfo()->getCoordenadas().getX();
    for(auto i: g.getVertexSet()){

        if(i->getInfo()->getCoordenadas().getX()<value){
            value = i->getInfo()->getCoordenadas().getX();
        }

    }
    return value;

}

double getMinY(Graph<VerticeInfo> &g){

    double value = g.getVertexSet()[0]->getInfo()->getCoordenadas().getY();
    for(auto i: g.getVertexSet()){
        if(i->getInfo()->getCoordenadas().getY()<value){
            value = i->getInfo()->getCoordenadas().getY();
        }

    }
    return value;

}
