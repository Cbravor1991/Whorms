#include "teletransportacion.h"
#include <string>

Teletransportacion::Teletransportacion(int x, int y) : x(x), y(y) {}

Teletransportacion::~Teletransportacion() {}

int Teletransportacion::disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos)
{

    b2Vec2 pos(x + 1, y + 1);
    disparador->SetTransform(pos, 0);
    disparador->ApplyLinearImpulse(b2Vec2(0.0, -1.0), disparador->GetWorldCenter(), true);
    return 0;
}

PosicionLanzable Teletransportacion::conseguir_posicion()
{
    return PosicionLanzable(1, x, y, 0, 0, false);
}