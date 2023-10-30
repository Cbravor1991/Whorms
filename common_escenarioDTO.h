

#ifndef ESCENARIODTO_H_
#define ESCENARIODTO_H_

#include <string>
#include <map>
#include <vector>
#include "common_socket.h"
#include "common_vigasDTO.h"


class EscenarioDTO
{
private:
std::vector<VigasDTO> vigas;
int cantidad_jugadores=0 ;


public:
    EscenarioDTO();

    void cargar_viga(VigasDTO viga);
    void cargar_cant_jugadores(int cantidad_jugadores_recibidos);

    int obtener_cantidad_jugadores();
};

#endif 
