#include "team_health.h"

TeamHealth::TeamHealth(): cantidad_jugadores(0) {}

void TeamHealth::actualizar(std::map<int, JugadorDTO> &jugadores)
{
    //para los jugadores que ya tengo, seteo la vida en 0
    for (auto const &[id, vida] : vida_por_equipo){
        if(vida_por_equipo.find(id) != vida_por_equipo.end())
        {
            vida_por_equipo.at(id) = 0;
        }
    }   

    for (auto const &[id_gusano, jugador] : jugadores)
    {      
        int id = jugador.obtenerIdCliente();
        int vida_jugador = jugador.obtener_vida();

        if(color_por_equipo.find(id) == color_por_equipo.end())
        {
            SDL_Color color = jugador.obtener_color();
            color_por_equipo.insert({id, color});
        }
        
        if(vida_por_equipo.find(id) == vida_por_equipo.end())
        {
            vida_por_equipo.insert({id, 0});
            cantidad_jugadores++;
        }
        
        vida_por_equipo.at(id) += vida_jugador;
    }

}

const std::map<int, int>& TeamHealth::obtenerVida() 
{
    return vida_por_equipo;
}

const std::map<int, SDL_Color>& TeamHealth::obtenerColores()
{
    return color_por_equipo;
}
