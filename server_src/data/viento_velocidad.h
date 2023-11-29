#include "data_DTO.h"

class VientoVelocidad : public Data
{
private:
    int velocidad;
    bool direccion;

public:
    VientoVelocidad(const VientoVelocidad &original)
    {
        // Copia superficial de datos
        velocidad = original.velocidad;
        direccion = original.direccion;
    }

    VientoVelocidad(int velocidad, bool direccion) : velocidad(velocidad), direccion(direccion) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_viento(velocidad, direccion);
    }
};
