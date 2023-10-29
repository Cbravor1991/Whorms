#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "client_protocol.h"
#include "common_state_game.h"
#include "common_liberror.h"
#include <tuple>

StateGame::StateGame()
{
    
}

void StateGame::cargar_escenario(EscenarioDTO escenario){
    escenario=escenario;
}
void StateGame::cargar_jugador(JugadorDTO jugador){
    jugador = jugador;

}
void StateGame::obtener_escenario(EscenarioDTO& escenario){
    escenario = escenario;
}
void StateGame::obtener_jugador(JugadorDTO& jugador){
    jugador = jugador;
}
    

