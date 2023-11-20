#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>
#include "action.h"

const int ATAQUE_AEREO = 1;

class Weapon : public Action {

  private:
  int tipo;
  

public:
    Weapon(int tipo): tipo(tipo){};
    void mandar_accion(ProtocoloCliente& protocolo){protocolo.enviar_arma(tipo);}
    virtual void render(SDL2pp::Renderer &renderer, TextureManager& tex_manager) {}
};

#endif