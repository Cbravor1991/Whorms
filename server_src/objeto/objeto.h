#ifndef OBJETO_H
#define OBJETO_H

#include "../../libs/box2d-2.4.0/include/box2d/box2d.h"
#include <string>
#include <memory>
#include <iostream>
#include <ostream>
#include "../data/posicion_lanzable.h"
#include "mundo.h"

class Mundo;

class Objeto
{
protected:
    Mundo *mundo;
    b2Body *body;
    bool is_dead;
    bool en_movimiento = false;
    // CollisionData collision_data;

public:
    Objeto(Mundo *mundo);
    virtual ~Objeto();

    bool consultar_movimiento();

    // Devuelve la posicion del objeto
    virtual PosicionLanzable conseguir_posicion() = 0;

    // Devuelve el cuerpo del objeto
    b2Body *getCuerpo();

    // Devuelve true si el objeto esta muerto
    bool esta_vivo();
};

#endif
