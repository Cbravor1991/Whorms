
#ifndef VIEW_H
#define VIEW_H
#include <map>
#include <string>
#include <vector>
#include "whorms.h"
#include <SDL2pp/SDL2pp.hh>
#include "../DTO/common_jugadorDTO.h"
#include "../DTO/common_vigaDTO.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>

class GameView
{

private: // agregar mixer, ttf, etc
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SDL2pp::SDLTTF ttf; // para render de letra

    SDL2pp::Texture background;
    Mixer mixer;
    Music music;

public:
    explicit GameView();

    void mostrar();
    void clear();
    SDL2pp::Renderer &getRenderer();

    void renderizar_texto(const std::string texto, int pos_x, int pos_y);
    void renderizar_viga(VigaDTO viga); // 140 20 70 20
    void renderizar_gusano(JugadorDTO jugador);
    void renderizar_fondo_pantalla();
    void reproducir_musica();

};

#endif // VIEW_H
