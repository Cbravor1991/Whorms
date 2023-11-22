#ifndef MUNDO_H
#define MUNDO_H

#include "../../libs/box2d-2.4.0/include/box2d/box2d.h"
#include "objeto.h"

class Mundo
{
private:
    b2World world;
    // Viento viento;

public:
    explicit Mundo(b2Vec2 gravity);
    ~Mundo();

    void agregar_viga(int x, int y, int largo, float_t angulo);

    // Inicializa un objeto recien agregado al mundo
    b2Body *crear_objeto(b2BodyDef body_def);

    // Remueve un objeto del mundo
    void eliminar_objeto(b2Body *body);

    b2Contact *recibir_contactos();

    void paso(float dt, int32 velocityIterations, int32 positionIterations);
};

#endif
