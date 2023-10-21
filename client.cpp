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

bool Cliente::run()
{
    std::string linea;
    while (conectado)
    {
        // Lee el los comandos desde la entrada estándar (stdin)
        while (std::getline(std::cin, linea))
        {
            if (!linea.empty() and linea[0] != '#')
            {
                ejecutar_accion(linea);
                if (!conectado)
                {
                    break;
                }
            }
        }
    }
    return true;
}

void Cliente::ejecutar_accion(const std::string &linea)
{
    // Tokeniza la línea para identificar la acción
    std::istringstream iss(linea);
    std::string action;
    iss >> action;
    if (action == CHAT)
    {
        // El cliente envía un mensaje de chat
        std::string chat_message;
        std::getline(iss >> std::ws, chat_message);
        protocolo.enviar_mensaje(chat_message);
        std::cout << chat_message << std::endl;
        conectado = protocolo.sigue_conectado();
    }
    else if (action == READ)
    {
        // El cliente espera recibir mensajes del servidor
        int n;
        if (iss >> n)
        {
            recibir_mensaje(n); // Reemplaza con tu función
        }
        else
        {
            std::cerr << "Formato incorrecto para la acción 'Read'" << std::endl;
        }
    }
    else if (action == EXIT)
    {
        conectado = false;
    }
    else
    {
        std::cerr << "Acción desconocida: " << action << std::endl;
    }
}

void Cliente::recibir_mensaje(int cantidad)
{
    for (int i = 0; i < cantidad; ++i)
    {
        bool tipo_mensaje = protocolo.recibir_mensaje();
        conectado = protocolo.sigue_conectado();
        if (tipo_mensaje and conectado)
        {
            // Llamar a la función para procesar la cantidad de jugadores
            int cantidad_jugadores = protocolo.recibir_cantidad_jugadores();
            conectado = protocolo.sigue_conectado();
            std::cout << "Jugadores " << cantidad_jugadores
                      << ", esperando al resto de tus amigos…" << std::endl;
        }
        else if (conectado)
        {
            // Llamar a la función para procesar un chat
            std::string chat = protocolo.recibir_chat();
            conectado = protocolo.sigue_conectado();
            std::cout << chat << std::endl;
        }
    }
}
