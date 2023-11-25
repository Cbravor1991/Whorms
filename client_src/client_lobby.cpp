#include "client_lobby.h"
#include <cstring>
#include <utility>
#include <string>
#include <iostream>

Lobby::Lobby(const std::string &hostname, const std::string &servname): hostname(hostname), servname(servname) {}

void Lobby::start_game(){
  
  std::cout<<hostname<<'\n';
   std::cout<<servname<<'\n';
}






