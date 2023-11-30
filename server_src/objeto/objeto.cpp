#include "objeto.h"
#include <string>

Objeto::Objeto(Mundo *world) : mundo(world), body(NULL), is_dead(false)
{
}
Objeto::~Objeto()
{
    mundo->eliminar_objeto(body);
}

void Objeto::explotar_regresiva() {}

bool Objeto::consultar_movimiento()
{

    b2Vec2 velocidadLineal = body->GetLinearVelocity();
    float velocidadAngular = body->GetAngularVelocity();
    // Define una velocidad mínima para considerar que el body está en movimiento.
    // Ajusta este valor según tus necesidades.
    if (velocidadLineal.Length() > velocidad_minima || std::abs(velocidadAngular) > velocidad_minima)
    {
        return true; // Al menos un body está en movimiento.
    }
    else if (!esta_en_contacto())
    {
        return true;
    }
    en_movimiento = false;

    return false; // Ningún body está en movimiento.
}

bool Objeto::esta_en_contacto()
{
    b2Contact *contact = mundo->recibir_contactos();
    while (contact != nullptr)
    {

        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        // Comprueba si uno de los cuerpos es el cuadrado
        if (fixtureA->GetBody() == body || fixtureB->GetBody() == body)
        {
            return true;
        }
        contact = contact->GetNext();
    }
    return false;
}

bool Objeto::esta_vivo()
{
    return !is_dead;
}

b2Body *Objeto::getCuerpo() { return body; }
