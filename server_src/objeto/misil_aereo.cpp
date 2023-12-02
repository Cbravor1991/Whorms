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
    boxShape.SetAsBox(TAMANIO_X_BOMBA, TAMANIO_Y_BOMBA);
    b2FixtureDef fd;
    fd.shape = &boxShape;
    fd.density = 0.0f;
    fd.friction = 0.0f;
    fd.restitution = 0.0f;
    body->CreateFixture(&fd);
    float viento = mundo->recibir_velocidad_viento();
    body->ApplyLinearImpulse(b2Vec2(viento, -0.1), body->GetWorldCenter(), true);
    radio = configuracion.getRadioAtaqueAereo();
    danio = configuracion.getDanioAtaqueAereo();
}

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
            b2Body *otherBody = (fixtureA->GetBody() == body) ? fixtureB->GetBody() : fixtureA->GetBody();
            contactos += 1;
            if (otherBody->gusano or contactos > 10 or !consultar_movimiento())
            {
                b2Vec2 center = this->body->GetPosition();
                explotar(center);
                is_dead = true;
            }
        }
        contact = contact->GetNext();
    }
}

MisilAereo::~MisilAereo() {}

PosicionLanzable MisilAereo::conseguir_posicion()
{
    contacto();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA)
    {
        is_dead = true;
    }
    // contacto();
    return PosicionLanzable(1, x, y, 0, 270, is_dead);
}
