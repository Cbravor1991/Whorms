#ifndef FRAGMENTO_H
#define FRAGMENTO_H

#include "arma.h"
#include <string>

class Fragmento : public Arma
{

private:
    int tipo;

public:
    Fragmento(Mundo *world, b2Vec2 center, int danio, int radio, float angulo, int tipo);
    ~Fragmento();

    void contacto_explosivo();

    PosicionLanzable conseguir_posicion();
};

#endif
