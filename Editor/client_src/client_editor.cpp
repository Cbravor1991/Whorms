#include "./client_editor.h"
#include <cstring>
#include <utility>
#include <string>
#include <iostream>

Editor::Editor(){}

void Editor::crear_mapa(std::string fondo_pantalla,  std::string nombre_mapa)
{
    en_juego = true;
    Game juego;
    juego.crear_mapa(fondo_pantalla, nombre_mapa);
}

void Editor::editar_mapa(std::string nombre_mapa){
 
     en_juego = true;
     Game juego;
     int id_fondo;
     std::string fondo;
     juego.subir_mapa(nombre_mapa, id_fondo);
     if (id_fondo == 3) {
        fondo = "noche";
     } else if (id_fondo == 2) {
        fondo = "snow";
     } else {
        fondo = "dia";
     }
    juego.crear_mapa(fondo, nombre_mapa);
}