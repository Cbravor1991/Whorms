#include "inventario.h"
#include <map>
#include <string>

Inventario::Inventario()
{
    ammo[0] = 0;
    ammo[1] = 12;
    ammo[2] = 100;
    ammo[3] = 100;
    ammo[4] = 100;
    ammo[5] = 100;
    ammo[6] = 100;
    ammo[7] = 100;
    ammo[8] = 100;
    ammo[9] = 100;
    ammo[10] = 100;
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
    if (tipo >= 0 && tipo < static_cast<int>(ammo.size()))
    {
        arma_actual = tipo;
        return ammo[tipo];
    }
    else
    {
        std::cerr << "Error: Tipo de arma fuera de rango." << std::endl;
        return -1;
    }
}
