#include "data_DTO.h"
#include "posicion_jugador.h"

class PaqueteGusanos : public Data
{
private:
    std::vector<PosicionJugador> jugadores;

public:
    PaqueteGusanos(std::vector<PosicionJugador> jugadores) : jugadores(jugadores) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_cantidad_jugadores(jugadores.size());
        for (const PosicionJugador &jugador : jugadores)
        {
            jugador.enviar_data(protocolo);
        }
    }
};
