#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "client_sender.h"
// #include "common_liberror.h"

ClienteLanzador::ClienteLanzador(
    ProtocoloCliente &protocolo, Queue<uint8_t> &queue_sender, Queue<StateGame> &queue_receiver) : protocolo(protocolo), queue_sender(queue_sender), queue_receiver(queue_receiver), cliente_recibidor(protocolo, queue_receiver)
{
    cliente_recibidor.start();
}

void ClienteLanzador::autorizar_turno(bool turno)
{
    this->turno = turno;
}

void ClienteLanzador::run()
{
    std::string linea;
    // Lee el los comandos desde la entrada estándar (stdin)
    while (std::getline(std::cin, linea) && en_conexion)
    {
        if (!linea.empty() and linea[0] != '#')
        {
            ejecutar_accion(linea);
            if (!en_conexion)
            {
                break;
            }
        }
    }
}

void ClienteLanzador::ejecutar_accion(const std::string &linea)
{
    // Tokeniza la línea para identificar la acción
    std::istringstream iss(linea);
    std::string action;
    iss >> action;
    if (action == MOVE and turno)
    {
        // El cliente envía un mensaje de chat
        std::string chat_message;
        std::getline(iss >> std::ws, chat_message);
        protocolo.enviar_mensaje(chat_message);
        en_conexion = protocolo.check_en_conexion();
    }
    else if (action == SALIR)
    {
        cliente_recibidor.terminar();
        protocolo.desconectar();
        cliente_recibidor.join();
        en_conexion = false;
    }
    else if (turno)
    {
        std::cout << "Acción desconocida: " << action << std::endl;
    }
}

void ClienteLanzador::terminar()
{
    en_conexion = false;
}