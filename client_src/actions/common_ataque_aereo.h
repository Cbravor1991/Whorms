

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


public:
  
    void mandar_accion(ProtocoloCliente& protocolo) override { protocolo.enviar_arma(ATAQUE_AEREO);}


};

#endif //  CLIENT_H_
