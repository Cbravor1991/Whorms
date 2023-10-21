// Gusano.h
#ifndef GUSANO_H
#define GUSANO_H
#include "objeto.h"

class Gusano : public Objeto
{
public:
    Gusano()
    {
        direccion = 0;
    }
    // void interactuar() override;
};

#endif // GUSANO_H