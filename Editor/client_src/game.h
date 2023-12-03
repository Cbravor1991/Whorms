#ifndef GAME_H
#define GAME_H

#pragma once
#include <string>
#include "graphics/view.h"
#include <vector>
#include <map>
#include <set>
#include "DTO/common_objeto.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

class Game
{
private:
   
    GameView view;

    std::vector<Objeto> objetos_creados;
  
    
    bool spawns_automaticos = true;
    std::string nombre_mapa = "nuevo_mapa";
    std::string extension = ".yaml";
    std::string fondo_eleguido = " ";



    std::string objeto_renderizar = " ";
    std::vector<std::string> tipos_objetos;
    int contador_objetos = -1;
    int cantidad_objetos = 7;

public:
  
    explicit Game( );

    void crear_mapa(std::string fondo_seleccionado, std::string nombre_mapa_recibido);

    bool gameLoop();

    bool manejarEventos();

    void guardar_datos();


    void renderizar();
};
#endif // GAME_H