#include <string>
#include <map>
#include <vector>
#include "common_escenarioDTO.h"
#include <iostream>

EscenarioDTO::EscenarioDTO(): cantidad_jugadores(0)
{
}

void EscenarioDTO::cargar_viga(VigasDTO viga)
{
    vigas.push_back(viga);
}

void EscenarioDTO::cargar_cant_jugadores(int cantidad_jugadores_recibidos)
{

    cantidad_jugadores = cantidad_jugadores_recibidos;
}

int EscenarioDTO::obtener_cantidad_jugadores()
{
    return cantidad_jugadores;
}
