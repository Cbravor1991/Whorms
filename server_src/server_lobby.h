#ifndef SERVER_LOBBY_H_
#define SERVER_LOBBY_H_

#include <vector>
#include <string>
#include <fstream>
#include "server_protocol.h"
#include "../common_src/thread.h"
#include "lobby.h"

class ServerLobby : public Thread
{
private:
    ProtocoloServer *protocolo;
    Lobby *lobby;

public:
    ServerLobby(ProtocoloServer *protocolo, Lobby *lobby);

    void run() override;
};

#endif
