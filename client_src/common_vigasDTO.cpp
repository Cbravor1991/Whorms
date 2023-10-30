#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "common_vigasDTO.h"
#include <tuple>

VigasDTO::VigasDTO(): x(0), y(0), id(0), tipo(false)
{
}

void VigasDTO::cargar_tipo(bool &tipo_viga)
{
    tipo = tipo_viga;
}

bool VigasDTO::obtener_tipo()
{
    return tipo;
}

void VigasDTO::cargar_posicion_x(const int &posicion_x)
{
    x = posicion_x;
}

void VigasDTO::cargar_posicion_y(const int &posicion_y)
{
    y = posicion_y;
}

void VigasDTO::cargar_id(const int &id_jugador)
{
    id = id_jugador;
}

int VigasDTO::obtener_posicion_x()
{
    return x;
}

int VigasDTO::obtener_posicion_y()
{
    return y;
}

int VigasDTO::obtener_posicion_id()
{
    return id;
}
