

#ifndef STATEGAME_H_
#define STATEGAME_H_

#include <string>
#include <map>
#include <vector>
#include "common_socket.h"
#include "client_protocol.h"
#include "client_sender.h"
#include "client_protocol.h"
#include "common_escenarioDTO.h"
#include "common_jugadorDTO.h"

class StateGame
{
private:

EscenarioDTO escenario;
JugadorDTO jugador;





 
public:
    StateGame();
    void cargar_escenario(EscenarioDTO escenario);
    void cargar_jugador(JugadorDTO jugador);
    void obtener_escenario(EscenarioDTO& escenario);
    void obtener_jugador(JugadorDTO& jugador);
    





};

#endif 
