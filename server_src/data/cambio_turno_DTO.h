#include "data_DTO.h"

class CambioTurno : public Data
{
private:
    int id;
    int id_gusano;

public:
    CambioTurno(int id, int id_gusano) : id(id), id_gusano(id_gusano) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_turno(id, id_gusano);
    }
};
