#include "ataque_aereo.h"
#include <string>

AtaqueAereo::AtaqueAereo(int x, int y) : x(x), y(y) {}

AtaqueAereo::~AtaqueAereo() {}

int AtaqueAereo::disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos)
{
    float pos_x = x - 6 * 10 / 2;
    float pos_y = 250; // altura maxima
    for (int i = 0; i < 6; i++, pos_x += 2)
    {
        Objeto *misil = new MisilAereo(mundo, pos_x, pos_y, i);
        objetos->push_back(misil);
    };
    return 6;
}

PosicionLanzable AtaqueAereo::conseguir_posicion()
{
    return PosicionLanzable(1, x, y, 0, 0, false);
}
