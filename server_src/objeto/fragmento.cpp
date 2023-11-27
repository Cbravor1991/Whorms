#include "fragmento.h"
#include "arma.h"

Fragmento::Fragmento(Mundo *world, b2Vec2 center, int danio, int radio, float angulo, int tipo)
{
    this->danio = danio;
    this->radio = radio;
    mundo = world;
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = center;
    body = mundo->crear_objeto(bd);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f * 0.5f, 2.0f * 0.5f);
    b2FixtureDef fd;
    fd.shape = &boxShape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.0f;
    body->CreateFixture(&fd);
    int fuerza = 100;
    b2Vec2 linear_velocity(fuerza * cos(angulo),
                           abs(fuerza) * sin(angulo));
    body->ApplyLinearImpulse(linear_velocity, body->GetWorldCenter(), true);
}

Fragmento::~Fragmento() {}

void Fragmento::contacto_explosivo()
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
            if (otherBody->gusano or contactos > 5)
            {
                b2Vec2 center = this->body->GetPosition();
                explotar(center);
                is_dead = true;
            }
        }

        contact = contact->GetNext();
    }
}

PosicionLanzable Fragmento::conseguir_posicion()
{
    contacto_explosivo();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA)
    {
        is_dead = true;
    }
    return PosicionLanzable(1, x, y, 0, 0, is_dead);
}
