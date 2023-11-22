// TurnoGusano.cpp
#include "turno_gusano.h"
#include <iostream>
#include <algorithm>

TurnoGusano::TurnoGusano() : turno_actual(1) {}

bool TurnoGusano::vacio() { return gusanos.empty(); }

void TurnoGusano::cambiar_turno()
{
    if (gusanos.empty())
    {
        std::cout << "No hay gusanos para cambiar de turno." << std::endl;
    }

    turno_actual = (turno_actual + 1) % gusanos.size();
    std::cout << "TurnoGusano cambiado al jugador con ID " << turno_actual << std::endl;
}

void TurnoGusano::agregar_gusano(Gusano *gusano)
{
    gusanos.push_back(gusano);
}

Gusano *TurnoGusano::recibir_turno()
{
    return gusanos[turno_actual];
}

std::vector<PosicionJugador> TurnoGusano::recibir_posiciones_gusanos()
{
    std::vector<PosicionJugador> posicion_jugadores;
    for (auto it = gusanos.begin(); it != gusanos.end();)
    {
        PosicionJugador posicion = (*it)->conseguir_posicion_gusano();
        posicion_jugadores.push_back(posicion);

        if (!(*it)->esta_vivo())
        {
            // Eliminar gusano si no está vivo+
            delete *it;
            it = gusanos.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return posicion_jugadores;
}

bool TurnoGusano::consultar_movimiento()
{
    for (Gusano *gusano : gusanos)
    {
        if (gusano->consultar_movimiento())
        {
            return true;
        }
    }
    return false;
}

TurnoGusano::~TurnoGusano()
{
    for (Gusano *gusano : gusanos)
    {
        delete gusano;
    }
    // Limpiar el vector después de liberar la memoria
    gusanos.clear();
}