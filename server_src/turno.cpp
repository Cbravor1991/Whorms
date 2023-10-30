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
        return 0;
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
        if (turno_actual >= jugadores.size())
        {
            turno_actual = 0; // Ajustar el turno actual si es mayor que la cantidad de jugadores restantes
        }
        std::cout << "ID " << id << " eliminado." << std::endl;
    }
    else
    {
        std::cout << "ID " << id << " no encontrado." << std::endl;
    }
}

void Turno::agregar_id(int id)
{
    jugadores.push_back(id);
}
