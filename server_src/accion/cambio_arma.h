#include "accion.h"

class CambioArma : public Accion
{
private:
    int tipo_arma;

public:
    CambioArma(int id, int tipo_arma) : Accion(id), tipo_arma(tipo_arma) {}
    int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva) override
    {
        if (!cuenta_regresiva)
        {
            escenario.equipar_arma(jugador_id, tipo_arma);
        }
        return -1;
    }
};