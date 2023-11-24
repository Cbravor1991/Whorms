// Turno.cpp
#include "turno.h"
#include <iostream>
#include <algorithm>

Turno::Turno() : turno_actual(0) {}

int Turno::cambiar_turno()
{
    if (jugadores.empty())
    {
        std::cout << "No hay jugadores para cambiar de turno." << std::endl;
        return VACIO;
    }

    turno_actual = (turno_actual + 1) % jugadores.size();
    std::cout << "Turno cambiado al jugador con ID " << jugadores[turno_actual] << std::endl;
    return jugadores[turno_actual];
}

void Turno::eliminar_id(int id)
{
    auto it = std::find(jugadores.begin(), jugadores.end(), id);
    if (it != jugadores.end())
    {
        jugadores.erase(it);
        std::cout << "ID " << id << " eliminado." << std::endl;
    }
    else
    {
        std::cout << "ID " << id << " no encontrado." << std::endl;
    }
    if (turno_actual != 0)
    {
        turno_actual--;
    }
}

void Turno::agregar_id(int id)
{
    if (jugadores.empty())
    {
        cambiar_turno();
    }
    jugadores.push_back(id);
}

int Turno::recibir_turno()
{
    if (jugadores.empty())
    {
        return VACIO;
    }
    return jugadores[turno_actual];
}
