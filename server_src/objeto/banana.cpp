#include "banana.h"
#include <string>

Banana::Banana(bool direccion, int angulo)
{

    this->angulo = angulo * (M_PI / 180);
    fuerza = 10000;
    if (!direccion)
    {
        fuerza = -10000;
    }
}

Banana::Banana(Mundo *mundo, b2Body *cuerpo)
{
    this->mundo = mundo;
    body = cuerpo;
    damanio = 10;
    velocidad_minima = 1.2f;
}

int Banana::disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos)
{
    this->mundo = mundo;
    b2Vec2 posicion = disparador->GetPosition();
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    b2Vec2 spawn(posicion.x, posicion.y + 20);
    bd.position = spawn;
    b2Body *body = mundo->crear_objeto(bd);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = 3 / 2;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0.5f;
    fixtureDef.restitution = 9;
    body->CreateFixture(&fixtureDef);
    b2Vec2 linear_velocity(fuerza * cos(angulo + disparador->angle),
                           abs(fuerza) * sin(angulo + disparador->angle));
    body->ApplyLinearImpulse(linear_velocity, body->GetWorldCenter(), true);
    Objeto *banana = new Banana(mundo, body);
    objetos->push_back(banana);
    return 0;
}

PosicionLanzable Banana::conseguir_posicion()
{
    contacto();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA or !consultar_movimiento() or contactos > 200)
    {
        is_dead = true;
        std::cout << "bana X = " << posicion.x << ", Y = " << posicion.y << std::endl;
    }
    return PosicionLanzable(1, x, y, 0, 0, is_dead);
}

Banana::~Banana() {}
