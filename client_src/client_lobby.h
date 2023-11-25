#ifndef LOBBY_H
#define LOBBY_H

#pragma once
#include "./game.h"
#include <optional>
#include <vector>
#include <string>
#include <QApplication>


class Lobby
{
private:

const std::string hostname;
const std::string servname;



   
public:
    
    Lobby(const std::string &hostname, const std::string &servname);

    void start_game();

  
};
#endif
