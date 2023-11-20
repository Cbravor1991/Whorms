

#include "common_paqueteDTO.h"

PaqueteDTO::PaqueteDTO(std::vector<JugadorDTO> jugadores, std::vector<ObjetoDTO> objetos) : jugadores(jugadores), objetos(objetos) {}

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

std::vector<ObjetoDTO> PaqueteDTO::obtener_objetos()
{
    return objetos;
}