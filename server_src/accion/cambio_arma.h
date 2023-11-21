#include "accion.h"

class CambioArma : public Accion
{
private:
    int tipo_arma;

public:
    CambioArma(int id, int tipo_arma) : Accion(id), tipo_arma(tipo_arma) {}
    void ejecutar_accion(Escenario &escenario) override
    {
        escenario.equipar_arma(1, jugador_id, tipo_arma);
    }
};