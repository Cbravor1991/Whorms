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
            int worm_damage = abs(this->danio * (1 - distance / (2 * this->radio)));

            closest->vida -= worm_damage;
        }
    }
}

void Arma::contacto()
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
            if (otherBody->gusano)
            {
                otherBody->vida -= danio;
                is_dead = true;
            }
        }
        contact = contact->GetNext();
    }
}