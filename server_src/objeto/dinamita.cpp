#include "dinamita.h"
#include <string>

Dinamita::Dinamita(bool direccion, int segundos)
{
    tiempo_hasta_explotar = segundos;
    this->angulo = angulo * (M_PI / 180);
    fuerza = 9;
    if (!direccion)
    {
        fuerza = -9;
    }
}

Dinamita::Dinamita(Mundo *mundo, b2Body *cuerpo, int segundos)
{
    tiempo_hasta_explotar = segundos;
    esperando_a_explotar = true;
    this->mundo = mundo;
    body = cuerpo;
    danio = configuracion.getDanioDinamita();
    radio = configuracion.getRadioDinamita();
    velocidad_minima = 1.2f;
}

int Dinamita::disparar(Mundo *mundo, b2Body *disparador)
{
    this->mundo = mundo;
    b2Vec2 posicion = disparador->GetPosition();
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    b2Vec2 spawn(posicion.x + fuerza, posicion.y + 5);
    bd.position = spawn;
    b2Body *body = mundo->crear_objeto(bd);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(TAMANIO_X_BOMBA, TAMANIO_Y_BOMBA);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 5.0f;
    body->CreateFixture(&fixtureDef);
    Objeto *dinamita = new Dinamita(mundo, body, tiempo_hasta_explotar);
    mundo->agregar_objeto(dinamita);
    return 0;
}

PosicionLanzable Dinamita::conseguir_posicion()
{
    // contacto();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA)
    {
        is_dead = true;
    }
    return PosicionLanzable(DYNAMITE, x, y, 0, 0, is_dead);
}

void Dinamita::explotar_regresiva()
{
    b2Vec2 center = this->body->GetPosition();
    explotar(center);
    is_dead = true;
}

void Dinamita::contacto()
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
            if (otherBody->gusano)
            {
                b2Vec2 center = this->body->GetPosition();
                explotar(center);
                is_dead = true;
            }
        }
        contact = contact->GetNext();
    }
}

Dinamita::~Dinamita() {}
