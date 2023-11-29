#ifndef DINAMITA_H
#define DINAMITA_H

#include "arma.h"
#include <string>

class Dinamita : public Arma
{
private:
public:
    Dinamita(bool direccion, int segundos);
    Dinamita(Mundo *mundo, b2Body *cuerpo, int segundos);
    ~Dinamita();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    void contacto();

    void explotar_regresiva();

    PosicionLanzable conseguir_posicion();
};

#endif
