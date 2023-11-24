#ifndef COMMON_PAQUETEDTO_H
#define COMMON_PAQUETEDTO_H

#include <string>
#include <map>
#include <vector>
#include "common_jugadorDTO.h"
#include "common_objetoDTO.h"
#include "common_state_game.h"

class JugadorDTO;

class PaqueteDTO : public StateGame
{
private:
    std::vector<JugadorDTO> jugadores;
    std::vector<ObjetoDTO> objetos;

public:
    PaqueteDTO(std::vector<JugadorDTO> jugadores, std::vector<ObjetoDTO> objetos);

    void cambiar_render(bool &permiso);

    std::vector<JugadorDTO> obtener_jugadores();

    std::vector<ObjetoDTO> obtener_objetos();
};

#endif