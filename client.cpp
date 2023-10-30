#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "client_protocol.h"
#include "client.h"
#include "common_liberror.h"
#include <tuple>

Cliente::Cliente(const std::string &hostname,
                 const std::string &servname) : hostname(hostname),
                                                servname(servname),
                                                protocolo(hostname, servname)

{
}

void Cliente::run()
{
    ClienteLanzador cliente_lanzador(protocolo, queue_sender, queue_receiver);
    cliente_lanzador.start();
    cliente_lanzador.join();
    protocolo.desconectar();
}

    void Cliente::cargar_id_jugador( uint8_t id){
        id = id;
    }
    uint8_t Cliente::obtener_id_jugador(){
        return id;
    };



