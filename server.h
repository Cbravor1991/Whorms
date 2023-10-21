
#ifndef SERVER_H_
#define SERVER_H_

#include <vector>
#include <string>
#include <fstream>
#include "common_socket.h"
#include "thread.h"
#include "server_acceptor.h"

const char SALIR = 'q';

class Server
{
private:
    const std::string servname;
    MonitorJugadores *monitor;

public:
    explicit Server(const std::string &servname);

    void run();

    /*
     * Deshabilito copias
     */
    Server(const Server &) = delete;
    Server &operator=(const Server &) = delete;
};

#endif //  SERVERL_H_
