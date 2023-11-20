#ifndef __MUNDO_H__
#define __MUNDO_H__

#include "../../libs/box2d-2.4.0/include/box2d/box2d.h"
#include "objeto.h"

class Mundo
{
private:
    b2World world;
    // Viento viento;
    // CollisionListener collision_listener;

    // Agrega todos los fragmentos de armas al mundo
    // void addAllFragments();

public:
    explicit Mundo(b2Vec2 gravity);
    ~Mundo();

    void agregar_viga(int x, int y, int largo, float_t angulo);

    // Inicializa un objeto recien agregado al mundo
    b2Body *crear_objeto(b2BodyDef body_def);

    // Remueve un objeto del mundo
    void eliminar_objeto(Objeto *objeto);

    b2Contact *recibir_contactos();

    void paso(float dt, int32 velocityIterations, int32 positionIterations);

    // Agrega un fragmento de arma
    // void addWeaponFragment(physical_object_ptr fragment);

    // Elimina una arma del mundo
    // void removeTimedWeapon(Weapon &weapon);

    // Setea la velocidad de un objeto
    // void setLinearVelocity(PhysicalObject &object, b2Vec2 &velocity);

    // Devuelve true si alguno de los objetos esta en movimiento
    // bool isActive();

    // Actualiza el mundo
    // void update();

    // Devuelve la velocidad del viento
    // float getWind() const;

    // Devuelve el objeto mas cercano entre al centro en la direccion end - center
    // b2Body *getClosestObject(RayCastWeaponExploded *callback,
    //                       b2Vec2 center, b2Vec2 end);
};

#endif
