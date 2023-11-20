#include "accion.h"

class UsoArma : public Accion
{
private:
    Arma *arma;

public:
    UsoArma(int id, Arma *arma) : Accion(id), arma(arma) {}
    int ejecutar_accion(Escenario &escenario) override
    {

        escenario.usar_arma(1, jugador_id, arma);
        return -1;
    }
};