#include "data_DTO.h"

class Segundo : public Data
{
private:
    int segundo;

public:
    Segundo(int segundo) : segundo(segundo) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_segundos(segundo);
    }
};
