#ifndef TELETRANSPORTACION_H
#define TELETRANSPORTACION_H

#include <string>
#include "arma.h"

class Teletransportacion : public Arma
{
private:
    int x;
    int y;

public:
    Teletransportacion(int x, int y);
    ~Teletransportacion();
    PosicionLanzable conseguir_posicion();

    // Teletransporta al gusano
    int disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos) override;
};

#endif
