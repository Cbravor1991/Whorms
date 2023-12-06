#ifndef OBJETO_DTO_H_
#define OBJETO_DTO_H_

#include <string>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <SDL2pp/SDL2pp.hh>
#include "../graphics/texture_manager.h"
#include "../worm/weapon/worm_weapon.h"

class ObjetoDTO
{
private:
    int id;
    int x;
    int y;
    bool direccion;
    int angulo;
    bool is_running = true;  
    int run_phase = 0;
    int tipo;
    bool explosion;

    std::string obtener_path();
public:
    ObjetoDTO(int tipo,int x, int y, bool direccion, int angulo,  bool explosion);

    void mostrar() const;

    int obtenerId();

    void activa_animacion(bool permiso);

    void actualizar(ObjetoDTO jugador);

    void renderizar(SDL2pp::Renderer &renderer, TextureManager &tex_manager);

    int posicion_x();

    int posicion_y();

    bool exploto();
    
    int obtenerTipo();
};

#endif
