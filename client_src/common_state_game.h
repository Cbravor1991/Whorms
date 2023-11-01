

#ifndef STATEGAME_H_
#define STATEGAME_H_

#include <string>
#include <map>
#include <vector>
#include "common_escenarioDTO.h"
#include "common_jugadorDTO.h"
#include "common_jugadorDTO.h"
#include "common_vigasDTO.h"

class StateGame
{
private:
    EscenarioDTO escenario;
    std::vector<JugadorDTO> jugador;
    std::vector< VigasDTO> vigas;
 
    bool turno = false;
    int tipo_mensaje;

public:
    StateGame();
    void cargar_viga(VigasDTO &viga);
    std::vector< VigasDTO> obtener_viga();
    void cargar_escenario(EscenarioDTO &escenario);
    void cargar_tipo_mensaje(int tipo_mensaje);
    void cargar_turno(bool turno);
    int obtener_turno();
    int obtener_tipo_mensaje();
    void cargar_jugador(JugadorDTO &jugador);
    EscenarioDTO obtener_escenario();
    std::vector<JugadorDTO> obtener_jugador();
};

#endif
