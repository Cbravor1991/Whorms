#include "arma.h"

Arma::Arma() : Objeto(nullptr) {}
Arma::~Arma()
{
}

int Arma::disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos) { return 0; }

void Arma::explotar(const b2Vec2 &center)
{
    for (float angulo_radio = 0; angulo_radio < 360; angulo_radio += 5)
    {
        b2Vec2 end = center + this->radio *
                                  b2Vec2(cos(angulo_radio * (M_PI / 180)), sin(angulo_radio * (M_PI / 180)));
        b2Body *closest = this->mundo->getClosestObject(&explosion, center, end);
        if (closest)
        {
            float distance = b2Distance(center, closest->GetPosition());

            // Justo en el borde hace la mitad de danio
            int worm_damage = abs(this->damanio * (1 - distance / (2 * this->radio)));

            closest->vida -= worm_damage;
        }
    }
}
