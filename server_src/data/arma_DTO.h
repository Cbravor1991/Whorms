#include "data_DTO.h"

class EquipacionArma : public Data
{
private:
    int id;
    int id_gusano;
    int tipo;
    int ammo;

public:
    EquipacionArma(int id, int id_gusano, int tipo, int ammo) : id(id), id_gusano(id_gusano), tipo(tipo), ammo(ammo) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_arma(id, id_gusano, tipo, ammo);
    }
};
