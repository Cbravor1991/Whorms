#ifndef GRANADA_VERDE_H
#define GRANADA_VERDE_H

#include "arma.h"
#include <string>

class GranadaVerde : public Arma
{
private:
public:
    GranadaVerde(bool direccion, int angulo, int segundos);
    GranadaVerde(Mundo *mundo, b2Body *cuerpo, int segundos);
    ~GranadaVerde();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    void contacto();

    void explotar_regresiva();

    PosicionLanzable conseguir_posicion();
};

#endif
