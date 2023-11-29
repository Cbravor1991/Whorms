#include "viento.h"
#include <random>

Viento::Viento() : min_velocity(0),
                   max_velocity(10)
{
    this->cambiar();
}

Viento::~Viento() {}

float Viento::getVelocity() const
{
    return this->velocity;
}

VientoVelocidad Viento::cambiar()
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<float> dist(min_velocity, max_velocity);
    std::uniform_int_distribution<int> direction(-1, 1); // Acepto velocidad 0

    this->velocity = dist(rng) * 10;
    this->velocity *= direction(rng);

    int velocidad = velocity;
    int direccion = direction(rng);
    if (direccion == -1)
    {
        direccion = 0; // Si la dirección es -1, cambia el signo de la velocidad
    }
    bool direccion_bool = static_cast<bool>(direction(rng));

    VientoVelocidad viento(velocidad, direccion_bool);
    return viento;
}
