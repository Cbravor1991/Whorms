
#ifndef VIEW_H
#define VIEW_H
#include <map>
#include <string>
#include <vector>
#include "whorms.h"
#include <SDL2pp/SDL2pp.hh>
#include "../DTO/common_jugadorDTO.h"
#include "../DTO/common_vigaDTO.h"

class GameView
{

private: // agregar mixer, ttf, etc
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SDL2pp::SDLTTF ttf; // para render de letra

public:
    explicit GameView();

    void mostrar();
    void clear();
    SDL2pp::Renderer &getRenderer();

    void renderizar_texto(const std::string texto, int pos_x, int pos_y);
    void renderizar_viga(VigaDTO viga); // 140 20 70 20
    void renderizar_gusano(JugadorDTO jugador);
    void renderizar_fondo_pantalla();
};

#endif // VIEW_H
