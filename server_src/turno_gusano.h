
#ifndef TURNO_GUSANO_H
#define TURNO_GUSANO_H

#include <vector>
#include <cstddef>
#include "objeto/gusano.h"

class TurnoGusano
{
public:
    TurnoGusano();
    ~TurnoGusano();
    bool consultar_movimiento();
    void cambiar_turno();
    bool vacio();
    void eliminar_id(int id);
    void agregar_gusano(Gusano *gusano);
    Gusano *recibir_turno();
    std::vector<PosicionJugador> recibir_posiciones_gusanos();

private:
    std::vector<Gusano *> gusanos;
    size_t turno_actual;
};

#endif