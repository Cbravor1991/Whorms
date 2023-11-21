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
// #include "../weapons/weapon.h"
// #include "../weapons/common_ataque_aereo.h"
#include "../worm/worm_status.h"
#include "../worm/worm_walk.h"
#include "../worm/worm_idle.h"

#include "../worm/weapon/worm_weapon.h"
#include "../worm/weapon/worm_airstrike.h"
#include "../worm/weapon/worm_no_weapon.h"
#include "../worm/weapon/worm_teleport.h"

class JugadorDTO
{
private:
    int id;
    int x;
    int y;
    bool direccion;
    int angulo;
    int run_phase = 0; // run animation phase
    int arma;
    std::shared_ptr<WormWeapon> weapon;
    int vida;
    bool is_running;//me indica si cambio el estado de IDLE a WALK
    SDL_Color color;
    //WormStatus* status;
    std::shared_ptr<WormStatus> status; //= std::make_unique<WormIdle>();

public:
    JugadorDTO(int id, int x, int y, bool direccion, int angulo, int vida, bool en_movimiento);

    void cargar_armas(int arma);

    void mostrar() const;

    int obtenerId();

    void activa_animacion(bool permiso);

    void actualizar(JugadorDTO jugador);

    void renderizar(SDL2pp::Renderer &renderer, TextureManager &tex_manager);

    int posicion_x();

    int posicion_y();

    int obtener_vida();

    SDL_Color obtener_color();

    void stop_running();
};

#endif
