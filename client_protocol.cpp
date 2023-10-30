#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "client_protocol.h"
#include "common_liberror.h"
#include <tuple>

ProtocoloCliente::ProtocoloCliente(const std::string &hostname,
                                   const std::string &servname) : socket(hostname.c_str(), servname.c_str())
{
}



int ProtocoloCliente::recibir_id_jugador()
{
    bool was_closed = false;
    uint8_t buffer;
    socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    int valor_entero = static_cast<int>(buffer);


    return valor_entero;
}




int ProtocoloCliente::recibir_id_turno_actual()
{
    bool was_closed = false;
    uint8_t buffer;
    socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    int valor_entero = static_cast<int>(buffer);

    return valor_entero;
}

void ProtocoloCliente::enviar_mensaje(const std::string &mensaje)
{
    bool was_closed = false;

    // Convierte la cadena a un número entero
    int numero = std::stoi(mensaje);

    int8_t byte = static_cast<int8_t>(numero);

    // Envía el byte
    socket.sendall(&byte, 1, &was_closed);

    if (was_closed)
    {
        en_conexion = false;
    }
}

int ProtocoloCliente::recibir_mensaje()
{
    bool was_closed = false;
    uint8_t buffer;
    try
    {

        socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
        if (was_closed)
        {
            en_conexion = false;
        }
        return traducir_tipo_mensaje(buffer);
    }
    catch (const std::exception &err)
    {
        return 1;
    }
}

void ProtocoloCliente::recibir_jugador(JugadorDTO & jugador)
{
    bool was_closed = false;
    int id;
    int x;
    int y;

    // Recibir el ID del jugador
    socket.recvall(&(id), BYTES_ID, &was_closed);
    jugador.cargar_id_turno_jugador(ntohs(id));

    if (was_closed)
    {
        en_conexion = false;

    }

    // Recibir la coordenada X
    socket.recvall(&(x), BYTES_X, &was_closed);
    jugador.cargar_posicion_x(ntohs(x));

    if (was_closed)
    {
        en_conexion = false;

    }

    // Recibir la coordenada Y
    socket.recvall(&(y), BYTES_Y, &was_closed);
    jugador.cargar_posicion_y(ntohs(y));

    if (was_closed)
    {
        en_conexion = false;
      
    }

  
}

VigasDTO ProtocoloCliente::recibir_viga()
{
    bool was_closed = false;
    bool viga_tipo;
    int x;
    int y;
    VigasDTO viga;

    // Recibir el tipo de viga
    socket.recvall(&(viga_tipo), BYTES_TIPO, &was_closed);
    viga.cargar_tipo(viga_tipo);


    if (was_closed)
    {
        en_conexion = false;
        return viga;
    }

    // Recibir la coordenada X
    socket.recvall(&(x), BYTES_X, &was_closed);
    viga.cargar_posicion_x(ntohs(x));

    if (was_closed)
    {
        en_conexion = false;
        return viga;
    }

    // Recibir la coordenada Y
    socket.recvall(&(y), BYTES_Y, &was_closed);
    viga.cargar_posicion_x(ntohs(y));

    if (was_closed)
    {
        en_conexion = false;
        return viga;
    }

    return viga;
}

int ProtocoloCliente::recibir_cantidad_jugadores()
{
    bool was_closed = false;
    uint8_t buffer;
    socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    int cantidad = traducir_mensaje_cantidad(buffer);
    return cantidad;
}

int ProtocoloCliente::traducir_tipo_mensaje(const uint8_t &buffer)
{
    int tipo;
    if (buffer == CANT_JUGADORES)
    {
        tipo = 0;
    }
    else if (buffer == RECIBIR_JUGADOR)
    {
        tipo = 1;
    }
    else if (buffer == RECIBIR_VIGA)
    {
        tipo = 2;
    }
    else if (buffer == RECIBIR_TURNO)
    {
        tipo = 3;
    }
    return tipo;
}

int ProtocoloCliente::traducir_mensaje_cantidad(const uint8_t &buffer)
{
    return static_cast<int>(static_cast<unsigned char>(buffer));
}

void ProtocoloCliente::desconectar()
{
    en_conexion = false;
    socket.shutdown(2);
    socket.close();
}

bool ProtocoloCliente::check_en_conexion()
{
    return en_conexion;
}

StateGame ProtocoloCliente::procesar_mensaje(const int& id_jugador)
{   StateGame estado_juego;
    JugadorDTO jugador_dto;
    EscenarioDTO escenario_dto;
    jugador_dto.cargar_id(id_jugador);

    int tipo_mensaje = recibir_mensaje();
    bool conectado = check_en_conexion();
    estado_juego.cargar_tipo_mensaje(tipo_mensaje);
    switch (tipo_mensaje)
    {
    case TIPO_CANTIDAD_JUGADORES:
        if (conectado)
        {   
            int cantidad_jugadores = recibir_cantidad_jugadores();
            conectado = check_en_conexion();
            std::cout << "Jugadores " << cantidad_jugadores
                      << ", esperando al resto de tus amigos…" << std::endl;
        }
           // escenario_dto.cargar_cant_jugadores(recibir_cantidad_jugadores());
            
        break;

    case TIPO_JUGADOR:
        if (conectado)
        {  

            recibir_jugador(jugador_dto);    
            conectado = check_en_conexion();
            std::cout << "Jugador " << jugador_dto.obtener_id() << " en coordenadas"
                      << " X: " << jugador_dto.obtener_posicion_x() << " Y: " << jugador_dto.obtener_posicion_y() << std::endl;



        }
        break;
    case TIPO_VIGA:
        if (conectado)
        {      
                   
           VigasDTO viga = recibir_viga();
            conectado = check_en_conexion();
            std::cout << "Viga " << viga.obtener_tipo() << " en coordenadas"
                      << " X: " << viga.obtener_posicion_x() << " Y: " << viga.obtener_posicion_y() << std::endl;
          
        }
        break;

    case TIPO_TURNO:
        if (conectado)
        {    int id =recibir_id_turno_actual();
            conectado = check_en_conexion();
            std::cout << "Turno jugador: " << id << std::endl;
        
          
        }
        break;
    }
    estado_juego.cargar_jugador(jugador_dto);
    estado_juego.cargar_escenario(escenario_dto);
  


 
    return estado_juego;
}

