

#include "common_paqueteDTO.h"

PaqueteDTO::PaqueteDTO(std::vector<JugadorDTO> jugadores) : jugadores(jugadores) {}

void PaqueteDTO::cambiar_render(bool &permiso)
{
    for (const JugadorDTO &jugador : jugadores)
    {
        jugador.mostrar();
    }
}

std::vector<JugadorDTO> PaqueteDTO::obtener_jugadores()
{
    return jugadores;
}
