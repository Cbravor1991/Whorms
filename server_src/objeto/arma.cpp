#include "arma.h"

Arma::Arma() : Objeto(nullptr) {}
Arma::~Arma()
{
}

int Arma::disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos) { return 0; }
