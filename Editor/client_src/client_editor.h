#ifndef EDITOR_H
#define EDITOR_H


#include "./game.h"
#include <optional>
#include <vector>
#include <string>
#include <QApplication>


class Editor
{
private:
  

public:
    explicit Editor();
    bool en_juego = false;
    void crear_mapa(std::string fondo_pantalla, std::string nombre_mapa);
    void editar_mapa(std::string nombre_mapa);

};
#endif
