#ifndef VIENTO_H
#define VIENTO_H

class Viento
{
private:
    float min_velocity;
    float max_velocity;
    float velocity;

public:
    explicit Viento();
    ~Viento();

    // Devuelve la velocidad del viento
    float getVelocity() const;

    // Actualiza la velocidad del viento
    void cambiar();
};

#endif
