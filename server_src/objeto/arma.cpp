#include "arma.h"
#include "fragmento.h"

Arma::Arma() : Objeto(nullptr) {}
Arma::~Arma()
{
}

int Arma::disparar(Mundo *mundo, b2Body *disparador) { return 0; }

int Arma::cuenta_regresiva() { return tiempo_hasta_explotar; }

void Arma::explotar_regresiva()
{
}

void Arma::mandar_fragmentos(int danio, int radio, int cantidad, int tipo)
{
    for (float grados = 0; grados < 360; grados += (360 / cantidad))
    {
        float_t angulo = grados * (M_PI / 180);
        b2Vec2 center = this->body->GetPosition() +
                        0.3 * b2Vec2(cos(angulo), sin(angulo));
        Objeto *fragmento = new Fragmento(mundo, center, danio, radio, angulo, tipo);
        mundo->agregar_objeto(fragmento);
    }
}

void Arma::explotar(const b2Vec2 &center)
{
    for (float angulo_radio = 0; angulo_radio < 360; angulo_radio += 1)
    {
        b2Vec2 end = center + this->radio *
                                  b2Vec2(cos(angulo_radio * (M_PI / 180)), sin(angulo_radio * (M_PI / 180)));
        b2Body *closest = this->mundo->getClosestObject(&explosion, center, end);

        if (closest)
        {
            float distance = b2Distance(center, closest->GetPosition());

            // Justo en el borde hace la mitad de danio
            int worm_damage = abs(this->danio * (1 - distance / (2 * this->radio)));
            closest->vida -= worm_damage;
        }
    }
}
