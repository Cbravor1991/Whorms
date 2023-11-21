#ifndef OBJETO_H
#define OBJETO_H

#include "../../libs/box2d-2.4.0/include/box2d/box2d.h"
#include <string>
#include <memory>
#include <iostream>
#include <ostream>
#include "../data/posicion_lanzable.h"

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

    // Destruye el cuerpo del objeto
    void destroyBody();

    // Devuelve la posicion del objeto
    virtual PosicionLanzable conseguir_posicion() = 0;

    // Devuelve el cuerpo del objeto
    b2Body *getCuerpo();

    // Devuelve true si el objeto se esta moviendo
    bool isMoving();

    // Devuelve true si el objeto esta activo
    bool isActive();

    // Devuelve true si el objeto esta muerto
    bool esta_vivo();

    // Devuelve true si el objeto es afectado por el viento
    bool isWindAffected();

    // Mata al objeto
    void kill();

    // Devuelve el id del objeto
    int getId();

    // Colisiona con otro objeto
    // virtual void collideWithSomething(CollisionData *other);
};

// typedef std::shared_ptr<Objeto> physical_object_ptr;

#endif
