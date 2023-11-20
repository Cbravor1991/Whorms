

#include <string>
#include <map>
#include <vector>
#include "common_jugadorDTO.h"
#include "common_objetoDTO.h"
#include "common_state_game.h"

class PaqueteDTO : public StateGame
{
private:
    std::vector<JugadorDTO> jugadores;
    std::vector<ObjetoDTO> objetos;

public:
    PaqueteDTO(std::vector<JugadorDTO> jugadores, std::vector<ObjetoDTO> objetos);

    void cambiar_render(bool &permiso);

    std::vector<JugadorDTO> obtener_jugadores();
};