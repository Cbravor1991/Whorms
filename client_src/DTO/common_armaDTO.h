

#include <string>
#include <map>
#include <vector>
#include "common_state_game.h"
#include <ostream>
#include <iostream>
#include "common_jugadorDTO.h"

class ArmaDTO : public StateGame
{
private:
    int id;
    int id_cliente;
    int arma;
    int ammo;

public:
    ArmaDTO(int id, int id_cliente, int arma, int ammo);
    void cambiar_render(bool &permiso);
    void cargar(std::map<int, JugadorDTO> &jugadores);
};
