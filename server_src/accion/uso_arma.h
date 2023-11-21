#include "accion.h"

class UsoArma : public Accion
{
private:
    Arma *arma;

public:
    UsoArma(int id, Arma *arma) : Accion(id), arma(arma) {}
    void ejecutar_accion(Escenario &escenario) override
    {

        escenario.usar_arma(1, jugador_id, arma);
    }
};