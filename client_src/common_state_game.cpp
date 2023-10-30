#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "common_state_game.h"
#include <tuple>

StateGame::StateGame()
{
}

void StateGame::cargar_turno(bool turno)
{
    this->turno = turno;
   
}

void StateGame::cargar_escenario(EscenarioDTO escenario)
{
    escenario = escenario;
}
void StateGame::cargar_jugador(JugadorDTO jugador)
{
    jugador = jugador;
}

int StateGame::obtener_turno()
{   
    return turno;
}

EscenarioDTO StateGame::obtener_escenario()
{
    return escenario;
}
JugadorDTO StateGame::obtener_jugador()
{
    return jugador;
}

void StateGame::cargar_tipo_mensaje(int tipo_mensaje)
{
    this->tipo_mensaje = tipo_mensaje;
}

int StateGame::obtener_tipo_mensaje()
{
    return tipo_mensaje;
}
