#include "data_DTO.h"

class EquipacionArma : public Data
{
private:
    int id;
    int tipo;
    int ammo;

public:
    EquipacionArma(int id, int tipo, int ammo) : id(id), tipo(tipo), ammo(ammo) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_arma(id, tipo, ammo);
    }
};
