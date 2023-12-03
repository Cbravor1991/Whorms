
#ifndef VIEW_H
#define VIEW_H
#include <map>
#include <string>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include "texture_manager.h"
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>

#include "../DTO/common_objeto.h"
using namespace SDL2pp;


class GameView
{

private: 
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SDL2pp::SDLTTF ttf; // para render de letra
    Mixer mixer;
    std::shared_ptr<SDL2pp::Chunk> sonido_actual;
	int canal_anterior;
    TextureManager tex_manager;

public:
    explicit GameView();

    void mostrar();
    void clear();
    SDL2pp::Renderer &getRenderer();//
    void renderizar_texto(const std::string texto, int pos_x, int pos_y, SDL_Color color);
    void renderizar_objeto(Objeto objeto);
    void mutear_sonidos();
    void reproducir_musica();
    void renderizar_fondo_pantalla(std::string fondo_seleccionado);





};

#endif // VIEW_H
