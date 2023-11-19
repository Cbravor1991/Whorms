

#ifndef ATAQUEAEREO_H_
#define ATAQUEAEREO_H_

#include <string>
#include <map>
#include <vector>
#include <optional>
#include "../DTO/common_jugadorDTO.h"
#include "weapon.h"



class AtaqueAereo : public Weapon
{

private:
 bool is_running = true;   // whether the character is currently running
 int run_phase = 0; // run animation phase

public:
    int x;
    int y;
    bool is_alive;  

    AtaqueAereo(int pos_x, int pos_y);
    void mandar_accion(ProtocoloCliente& protocolo) override { protocolo.enviar_arma(ATAQUE_AEREO);}
    void render(SDL2pp::Renderer &renderer, TextureManager& tex_manager) override; 


};

#endif //  CLIENT_H_
