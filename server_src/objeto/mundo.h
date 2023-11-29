#ifndef MUNDO_H
#define MUNDO_H

#include "../../libs/box2d-2.4.0/include/box2d/box2d.h"
#include "objeto.h"
#include "viento.h"
#include "RayCastWeaponExploded.h"

const int ALTURA_AGUA = 0;

class Objeto;

class Mundo
{
private:
    b2World world;
    std::vector<Objeto *> objetos;
    Viento viento;

public:
    explicit Mundo(b2Vec2 gravity);
    ~Mundo();

    b2Body *getClosestObject(RayCastWeaponExploded *callback,
                             b2Vec2 center, b2Vec2 end);

    void agregar_viga(int x, int y, int largo, float_t angulo);

    // Inicializa un objeto recien agregado al mundo
    b2Body *crear_objeto(b2BodyDef body_def);

    // Remueve un objeto del mundo
    void eliminar_objeto(b2Body *body);

    void agregar_objeto(Objeto *objeto);

    std::vector<PosicionLanzable> recibir_posiciones_objetos();

    void explotar_bombas_regresivas();

    bool en_movimiento();

    b2Contact *recibir_contactos();

    VientoVelocidad actualizar();

    float recibir_velocidad_viento();

    void paso(float dt, int32 velocityIterations, int32 positionIterations);
};

#endif
