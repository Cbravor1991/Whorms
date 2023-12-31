// Gusano.h
#ifndef GUSANO_H
#define GUSANO_H
#include "../../libs/box2d-2.4.0/include/box2d/box2d.h"
#include "../data/posicion_jugador.h"
#include "../inventario.h"
#include "objeto.h"
#include "mundo.h"

const float_t CAMINAR = 12.2;
const float_t SALTO_ADELANTE_X = 4.945; // X
const float_t SALTO_ADELANTE_Y = 10.4;  // Y
const float_t SALTO_ATRAS_X = 0.64;     // X
const float_t SALTO_ATRAS_Y = 15.86;

class Gusano : public Objeto
{
private:
    int direccion;
    Inventario inventario;
    float_t angulo_viga = 0;
    int id_cliente;
    int id_gusano;
    float altura;

public:
    int conseguir_id();
    bool usar_arma(Arma *arma);
    std::pair<int, int> cambiar_arma(int tipo);
    void cambiar_angulo_viga();
    Gusano(Mundo *mundo, b2Vec2 spawn, int id_cliente, int id_gusano);
    void mover_derecha();
    void mover_izquierda();
    void mover_arriba_adelante();
    void mover_arriba_atras();
    int getDireccion();
    PosicionJugador conseguir_posicion_gusano();
    PosicionLanzable conseguir_posicion();
    bool danio_recibido();
    // void interactuar() override;
};

#endif // GUSANO_H
