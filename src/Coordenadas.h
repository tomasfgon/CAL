//
// Created by neves on 20/05/2020.
//

#include "TipoLixo.h"

#ifndef PROJETO_COORDENADAS_H
#define PROJETO_COORDENADAS_H

#endif //PROJETO_COORDENADAS_H

class Coordenadas {
private:
    double x;
    double y;



public:
    Coordenadas(double primeiro, double segundo){
        x = primeiro;
        y = segundo;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        Coordenadas::y = y;
    }

    double getX() const {
        return x;
    }

    void setX(double x) {
        Coordenadas::x = x;
    }


};