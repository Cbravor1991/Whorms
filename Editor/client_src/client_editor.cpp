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
    // en_juego = true;
    // Game juego;
    // juego.subir_mapa(nombre_mapa);

}