#include <string>
#include <map>
#include <vector>
#include "common_socket.h"
#include "common_escenarioDTO.h"

EscenarioDTO::EscenarioDTO()
{
    
}

void EscenarioDTO::cargar_viga(VigasDTO viga) {
    vigas.push_back(viga);
}

void EscenarioDTO::cargar_cant_jugadores(int cantidad_jugadores) {
    cantidad_jugadores = cantidad_jugadores;
}

int EscenarioDTO::obtener_cantidad_jugadores() {
    return cantidad_jugadores;
}




