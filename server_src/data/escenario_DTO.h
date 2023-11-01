#include "data_DTO.h"
#include "posicion_viga.h"

class EscenarioInformacion : public Data
{
private:
    int tamanio_x;
    int tamanio_y;
    std::vector<PosicionViga> vigas;

public:
    EscenarioInformacion(int tamanio_x, int tamanio_y, std::vector<PosicionViga> vigas) : tamanio_x(tamanio_x), tamanio_y(tamanio_y), vigas(vigas) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_informacion_escenario(tamanio_x, tamanio_y, vigas.size());
        for (const PosicionViga &viga : vigas)
        {
            viga.enviar_data(protocolo);
        }
    }
};
