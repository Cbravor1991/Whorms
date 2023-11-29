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
    danio = configuracion.getDanioBanana();
    velocidad_minima = 1.2f;
}

int Banana::disparar(Mundo *mundo, b2Body *disparador)
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
    mundo->agregar_objeto(banana);
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
    }
    return PosicionLanzable(BANANA, x, y, 0, 0, is_dead);
}

void Banana::contacto()
{
    b2Contact *contact = mundo->recibir_contactos();
    while (contact != nullptr)
    {

        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        // Comprueba si uno de los cuerpos es el cuadrado
        if (fixtureA->GetBody() == body || fixtureB->GetBody() == body)
        {
            b2Body *otherBody = (fixtureA->GetBody() == body) ? fixtureB->GetBody() : fixtureA->GetBody();
            contactos += 1;
            if (otherBody->gusano)
            {
                otherBody->vida -= danio;
                is_dead = true;
            }
        }
        contact = contact->GetNext();
    }
}

Banana::~Banana() {}
