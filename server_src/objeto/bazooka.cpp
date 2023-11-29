#include "bazooka.h"
#include <string>

Bazooka::Bazooka(bool direccion, int angulo)
{

    this->angulo = angulo * (M_PI / 180);
    fuerza = 10000;
    if (!direccion)
    {
        fuerza = -10000;
    }
}

Bazooka::Bazooka(Mundo *mundo, b2Body *cuerpo)
{
    this->mundo = mundo;
    body = cuerpo;
    danio = configuracion.getDanioBazooka();
    radio = configuracion.getRadioBazooka();
    velocidad_minima = 1.2f;
}

int Bazooka::disparar(Mundo *mundo, b2Body *disparador)
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
    fixtureDef.restitution = 0;
    body->CreateFixture(&fixtureDef);
    b2Vec2 linear_velocity(fuerza * cos(angulo + disparador->angle),
                           abs(fuerza) * sin(angulo + disparador->angle));
    body->ApplyLinearImpulse(linear_velocity, body->GetWorldCenter(), true);
    Objeto *bazooka = new Bazooka(mundo, body);
    mundo->agregar_objeto(bazooka);
    return 0;
}

void Bazooka::contacto_explosivo()
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

PosicionLanzable Bazooka::conseguir_posicion()
{
    contacto_explosivo();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA or !consultar_movimiento())
    {
        is_dead = true;
    }
    return PosicionLanzable(BAZOOKA, x, y, 0, 0, is_dead);
}

Bazooka::~Bazooka() {}
