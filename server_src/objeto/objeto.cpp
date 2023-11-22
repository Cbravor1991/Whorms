#include "objeto.h"
#include <string>

Objeto::Objeto(Mundo *world) : mundo(world), body(NULL), is_dead(false)
{
}
Objeto::~Objeto() { mundo->eliminar_objeto(body); }

bool Objeto::consultar_movimiento()
{

    b2Vec2 velocidadLineal = body->GetLinearVelocity();
    float velocidadAngular = body->GetAngularVelocity();

    // Define una velocidad mínima para considerar que el body está en movimiento.
    float velocidadMinima = 0.0f; // Ajusta este valor según tus necesidades.

    if (velocidadLineal.Length() > velocidadMinima || std::abs(velocidadAngular) > velocidadMinima)
    {
        return true; // Al menos un body está en movimiento.
    }
    en_movimiento = false;
    return false; // Ningún body está en movimiento.
}

bool Objeto::esta_vivo()
{
    return !this->is_dead;
}

b2Body *Objeto::getCuerpo() { return body; }
