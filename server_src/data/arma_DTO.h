#include "data_DTO.h"

class Arma : public Data
{
private:
    int id;
    int tipo;

public:
    Arma(int id, int tipo) : id(id), tipo(tipo) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_arma(id, tipo);
    }
};
