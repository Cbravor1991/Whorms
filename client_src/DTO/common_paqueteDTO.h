

#include <string>
#include <map>
#include <vector>
#include "common_jugadorDTO.h"
#include "common_state_game.h"

class PaqueteDTO : public StateGame
{
private:
    std::vector<JugadorDTO> jugadores;

public:
    PaqueteDTO(std::vector<JugadorDTO> jugadores);

    void cambiar_render(bool &permiso);

    std::vector<JugadorDTO> obtener_jugadores();
};
