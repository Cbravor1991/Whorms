#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "common_liberror.h"
#include "server_acceptor.h"
#include "monitor_jugador.cpp"

ServerAceptador::ServerAceptador(
    const std::string &servname, MonitorJugadores *monitor) : socket(servname.c_str()),
                                                              monitor(monitor)
{
    escenario = new Escenario(200, 200, monitor);
    escenario->colocar_viga(50, 50, 0, 0);
    escenario->colocar_viga(40, 100, 1, 0);
    escenario->colocar_viga(70, 100, 0, 0);
}

void ServerAceptador::run()
{
    try
    {
        while (ejecutando)
        {
            Socket aceptado = socket.accept();
            lanzar_hilo_manejador(std::move(aceptado));
            monitor->limpiar_desconectados();
        }
        delete escenario;
    }
    catch (const std::exception &err)
    {
    }
}

void ServerAceptador::lanzar_hilo_manejador(
    Socket skt_cliente)
{
    ProtocoloServer *protocolo = new ProtocoloServer(std::move(skt_cliente));
    ServerLanzador *lanzador = new ServerLanzador(protocolo);
    ServerRecibidor *recibidor = new ServerRecibidor(escenario, protocolo);
    Jugador *jugador = new Jugador(protocolo, lanzador, recibidor);
    monitor->agregar_jugador(jugador);
}

void ServerAceptador::terminar()
{
    ejecutando = false;
    socket.shutdown(2);
    socket.close();
}
