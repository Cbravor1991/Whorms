#include "data.h"

class PosicionViga : public Data
{
private:
    bool tipo;
    int x;
    int y;

public:
    PosicionViga(bool tipo, int x, int y) : tipo(tipo), x(x), y(y) {}

    void enviar_data(ProtocoloServer *protocolo) override
    {
        protocolo->enviar_viga(tipo, x, y);
    }
};