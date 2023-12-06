#ifndef TEAM_HEALTH_H
#define TEAM_HEALTH_H

#include <map>
#include <SDL.h>
#include "../DTO/common_jugadorDTO.h"

class TeamHealth {

    std::map<int, int> vida_por_equipo;
    std::map<int, SDL_Color> color_por_equipo;
    int cantidad_jugadores;
    public:
    explicit TeamHealth();

    void actualizar(std::map<int, JugadorDTO> &jugadores);
    const std::map<int, int> &obtenerVida();
    const std::map<int, SDL_Color> & obtenerColores();
};



#endif
