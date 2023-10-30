#ifndef DATA_H_
#define DATA_H_

#include "../server_protocol.h"

class Data
{
public:
    Data() {}

    virtual void enviar_data(ProtocoloServer *protocolo) {}

    virtual ~Data() {}
};

#endif