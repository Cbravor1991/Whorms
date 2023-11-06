

#include <string>
#include <map>
#include <vector>
#include "common_vigaDTO.h"
#include "common_state_game.h"

class PaqueteDTO : public StateGame
{
private:
    std::vector<JugadorDTO> jugadores;

public:
    PaqueteDTO(std::vector<JugadorDTO> jugadores) : jugadores(jugadores) {}

    void cambiar_render(bool &permiso) override
    {
        for (const JugadorDTO &jugador : jugadores)
        {
            jugador.mostrar();
        }
    }
    
    std::vector<JugadorDTO> obtener_jugadores() {
        return jugadores;
    }
};
