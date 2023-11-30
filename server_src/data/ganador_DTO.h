#include "data_DTO.h"

class Ganador : public Data
{
private:
    int id_ganador;

public:
    Ganador(int id) : id_ganador(id) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_ganador(id_ganador);
    }
};
