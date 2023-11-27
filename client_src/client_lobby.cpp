#include "./client_lobby.h"
#include <cstring>
#include <utility>
#include <string>
#include <iostream>

Lobby::Lobby(const std::string &hostname, const std::string &servname): hostname(hostname), servname(servname), protocolo(hostname, servname) {
  
      partida = protocolo.recibir_partidas();
      escenarios = protocolo.recibir_escenarios();

}

void Lobby::enviar_partida (int partida){
  protocolo.enviar_modo(0);
  protocolo.enviar_partida(partida); 
  Game juego(protocolo);
  juego.run();
}

void Lobby::enviar_escenario (int escenario){
  protocolo.enviar_modo(1);
  protocolo.enviar_escenario(escenario); 
  Game juego(protocolo);
  juego.run();
}






