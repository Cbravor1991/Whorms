

#ifndef ESCENARIODTO_H_
#define ESCENARIODTO_H_

#include <string>
#include <map>
#include <vector>
#include "common_vigasDTO.h"

class EscenarioDTO
{
private:
    std::vector<VigasDTO> vigas;
    int cantidad_jugadores;

public:
    EscenarioDTO();

    void cargar_viga(VigasDTO viga);
    void cargar_cant_jugadores(int cantidad_jugadores_recibidos);

    int obtener_cantidad_jugadores();
};

#endif
