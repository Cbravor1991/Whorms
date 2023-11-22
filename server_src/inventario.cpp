#include "inventario.h"
#include <map>
#include <string>

Inventario::Inventario()
{
    ammo[0] = 0;
    ammo[1] = 12;
    ammo[2] = 100;
}

Inventario::~Inventario() {}

bool Inventario::disparar(Mundo *world, b2Body *posicion, Arma *arma, std::vector<Objeto *> *objetos)
{

    if (this->ammo[this->arma_actual] == 0)
    {
        return false;
    }
    int ammo_usada = arma->disparar(world, posicion, objetos);
    this->ammo[this->arma_actual] -= ammo_usada;
    arma_actual = 0;
    return true;
}

int Inventario::cambiar_arma(int tipo)
{
    arma_actual = tipo;
    return ammo[tipo];
}
