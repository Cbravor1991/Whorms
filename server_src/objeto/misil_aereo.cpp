#include "misil_aereo.h"
#include <string>

MisilAereo::MisilAereo(Mundo *world, float x, float y, int misil)
{
    mundo = world;
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    b2Vec2 spawn(x + misil, y);
    bd.position = spawn;
    body = mundo->crear_objeto(bd);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f * 0.5f, 2.0f * 0.5f);
    b2FixtureDef fd;
    fd.shape = &boxShape;
    fd.density = 0.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.0f;
    body->CreateFixture(&fd);
    body->ApplyLinearImpulse(b2Vec2(0.0, -0.1), body->GetWorldCenter(), true);
}

MisilAereo::~MisilAereo() {}

void MisilAereo::contacto()
{
    b2Contact *contact = mundo->recibir_contactos();
    while (contact != nullptr)
    {

        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        // Comprueba si uno de los cuerpos es el cuadrado
        if (fixtureA->GetBody() == body || fixtureB->GetBody() == body)
        {
        }
        contact = contact->GetNext();
    }
}

PosicionLanzable MisilAereo::conseguir_posicion()
{

    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    std::cout << "Misil X = " << posicion.x << ", Y = " << posicion.y << std::endl;
    if (y < 30 or !consultar_movimiento())
    {
        is_dead = true;
    }
    // contacto();
    return PosicionLanzable(1, x, y, 0, 0, is_dead);
}
