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

void Viento::cambiar()
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<float> dist(min_velocity, max_velocity);
    std::uniform_int_distribution<int> direction(-1, 1); // Acepto velocidad 0

    this->velocity = dist(rng);
    this->velocity *= direction(rng);
}
