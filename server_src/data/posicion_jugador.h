#include "data.h"

class PosicionJugador : public Data
{
private:
    int id;
    int x;
    int y;

public:
    PosicionJugador(int id, int x, int y) : id(id), x(x), y(y) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_jugador(id, x, y);
    }
};