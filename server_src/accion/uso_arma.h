#include "accion.h"

class UsoArma : public Accion
{
private:
    Arma *arma;

public:
    UsoArma(int id, Arma *arma) : Accion(id), arma(arma) {}
    int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva) override
    {
        if (!cuenta_regresiva)
        {
            escenario.usar_arma(jugador_id, arma);
            return arma->cuenta_regresiva();
        }
        return -1;
    }
};