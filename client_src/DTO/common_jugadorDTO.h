#ifndef JUGADORDTO_H_
#define JUGADORDTO_H_

#include <string>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2pp/SDL2pp.hh>
#include "../graphics/texture_manager.h"
//#include "../weapons/weapon.h"
//#include "../weapons/common_ataque_aereo.h"


class JugadorDTO
{
private:
    int id;
    int x;
    int y;
    bool direccion;
    int angulo;
    bool is_running;   // whether the character is currently running
    int run_phase = 0; // run animation phase
    int arma;
    int vida;
    SDL_Color color;

public:
    JugadorDTO(int id, int x, int y, bool direccion, int angulo);

    void cargar_armas(int arma);

    void mostrar() const;

    int obtenerId();

    void activa_animacion(bool permiso);

    void actualizar(JugadorDTO jugador);

    void renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager);

    int posicion_x();

    int posicion_y();

    int obtener_vida();

    SDL_Color obtener_color();
};

#endif
