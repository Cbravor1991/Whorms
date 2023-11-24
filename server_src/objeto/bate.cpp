#include "bate.h"
#include <string>

Bate::Bate(bool direccion, int angulo)
{

    this->angulo = angulo * (M_PI / 180);
    fuerza = 100000;
    if (!direccion)
    {
        fuerza = -100000;
    }
    damanio = 10;
    radio = 20;
}

int Bate::disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos)
{
    this->mundo = mundo;
    b2Vec2 posicion = disparador->GetPosition();
    angulo += disparador->angle;
    empujar(posicion);
    return 0;
}

void Bate::empujar(const b2Vec2 &center)
{
    int inicio = -360;
    int fin = 0;
    int incremento = 1;
    while (inicio != fin)
    {
        b2Vec2 end = center + this->radio *
                                  b2Vec2(cos(inicio * (M_PI / 180)), sin(inicio * (M_PI / 180)));
        b2Body *closest = this->mundo->getClosestObject(&explosion, center, end);
        if (closest and closest->gusano)
        {
            b2Vec2 linear_velocity(fuerza * cos(angulo), abs(fuerza) * sin(angulo));
            closest->ApplyLinearImpulse(linear_velocity, closest->GetWorldCenter(), true);
            closest->vida -= damanio;
            break;
        }
        inicio += incremento;
    }
}

PosicionLanzable Bate::conseguir_posicion()
{
    contacto();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA or !consultar_movimiento())
    {
        is_dead = true;
        std::cout << "bana X = " << posicion.x << ", Y = " << posicion.y << std::endl;
    }
    return PosicionLanzable(1, x, y, 0, 0, is_dead);
}

Bate::~Bate() {}
