#ifndef DATA_DTO_H_
#define DATA_DTO_H_

#include "../server_protocol.h"
#include "posicion_jugador.h"
#include "posicion_viga.h"
#include <iostream>

class Data
{
public:
    Data() {}

    virtual void enviar_data(ProtocoloServer *protocolo)
    {
    }

    virtual ~Data() {}
};

#endif