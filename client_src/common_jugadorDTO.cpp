#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "common_jugadorDTO.h"
#include <tuple>

JugadorDTO::JugadorDTO(): x(0), y(0), id(0), id_jugador_turno_actual(0), turno_activo(false)
{
}

void JugadorDTO::cargar_posicion_x(const int &posicion_x)
{
    x = posicion_x;
}

void JugadorDTO::cargar_posicion_y(const int &posicion_y)
{
    y = posicion_y;
}

void JugadorDTO::cargar_id(const int &id_jugador)
{
    id = id_jugador;
}

void JugadorDTO::cargar_id_turno_jugador(const int &id_jugador)
{
    id_jugador_turno_actual = id_jugador;
}

int JugadorDTO::obtener_posicion_x()
{
    return x;
}

int JugadorDTO::obtener_posicion_y()
{
    return y;
}

int JugadorDTO::obtener_id()
{
    return id;
}

int JugadorDTO::obtener_id_turno_jugador()
{
    return id_jugador_turno_actual;
}

void JugadorDTO::cargar_turno(bool turno)
{
    turno_activo = turno;
}

bool JugadorDTO::obtener_turno()
{  
    return turno_activo;
}
