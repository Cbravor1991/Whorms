#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "objeto/arma.h"
#include "objeto/mundo.h"
#include <map>
#include <string>

class Inventario
{
private:
    std::map<int, int> ammo;
    int arma_actual;

public:
    Inventario();

    ~Inventario();

    // Devuelve si puede disparar el arma, y disminuye la municion
    bool disparar(Mundo *world, b2Body *posicion, Arma *arma, std::vector<Objeto *> *objetos);

    // Cambia el arma actual
    int cambiar_arma(int tipo);
};

#endif
