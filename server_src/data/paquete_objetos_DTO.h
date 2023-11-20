#include "data_DTO.h"
#include "posicion_lanzable.h"

class PaqueteObjetos : public Data
{
private:
    std::vector<PosicionLanzable> objetos;

public:
    PaqueteObjetos(std::vector<PosicionLanzable> objetos) : objetos(objetos) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_cantidad_objetos(objetos.size());
        for (const PosicionLanzable &objeto : objetos)
        {
            objeto.enviar_data(protocolo);
        }
    }
};
