#include "data.h"

class CambioTurno : public Data
{
private:
    int id;

public:
    CambioTurno(int id) : id(id) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_turno(id);
    }
};