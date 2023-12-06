// Turno.cpp
#include "turno.h"
#include <iostream>
#include <algorithm>

Turno::Turno() : turno_actual(-1) {}

int Turno::cambiar_turno()
{
    if (jugadores.empty())
    {
        return VACIO;
    }

    turno_actual = (turno_actual + 1) % jugadores.size();
    return jugadores[turno_actual];
}

void Turno::eliminar_id(int id)
{
    auto it = std::find(jugadores.begin(), jugadores.end(), id);
    if (it != jugadores.end())
    {
        jugadores.erase(it);
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

std::vector<int> Turno::obtener_jugadores()
{
    return jugadores;
}
