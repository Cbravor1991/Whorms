#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "common_jugadorDTO.h"
#include "common_liberror.h"
#include <tuple>

JugadorDTO::JugadorDTO()
{
    
}



void JugadorDTO::cargar_posicion_x(const int& posicion_x) {
  x= posicion_x;
}

void JugadorDTO::cargar_posicion_y(const int& posicion_y) {
  y= posicion_y;
}

void JugadorDTO::cargar_id(const int& id_jugador) {
  id= id_jugador;
}

int JugadorDTO::obtener_posicion_x(){
    return x;
}

int JugadorDTO::obtener_posicion_y(){
    return y;
}

int JugadorDTO::obtener_posicion_id(){
    return id; 
}

