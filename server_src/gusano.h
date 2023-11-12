// Gusano.h
#ifndef GUSANO_H
#define GUSANO_H
#include "../libs/box2d-2.4.0/include/box2d/box2d.h"
#include "data/posicion_jugador.h"

const float_t CAMINAR = 12.2;
const float_t SALTO_ADELANTE_X = 4.945; // X
const float_t SALTO_ADELANTE_Y = 10.4;  // Y
const float_t SALTO_ATRAS_X = 0.64;     // X
const float_t SALTO_ATRAS_Y = 15.86;

class Gusano
{
private:
    int direccion;
    b2Body *cuerpo;
    float_t angulo_viga = 0;

public:
    void cambiar_angulo_viga(b2Contact *contact);
    Gusano(b2Body *cuerpo);
    void mover_derecha(b2Contact *contact);
    void mover_izquierda(b2Contact *contact);
    void mover_arriba_adelante(b2Contact *contact);
    void mover_arriba_atras(b2Contact *contact);
    int getDireccion();
    PosicionJugador GetPosicion(int id);
    b2Body *getCuerpo();
    // void interactuar() override;
};

#endif // GUSANO_H
