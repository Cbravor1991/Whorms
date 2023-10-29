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


