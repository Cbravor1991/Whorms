
#ifndef VIEW_H
#define VIEW_H
#include <map>
#include <string>
#include <vector>
#include "whorms.h"
#include <SDL2pp/SDL2pp.hh>
#include "../DTO/common_jugadorDTO.h"
#include "../DTO/common_vigaDTO.h"
#include "texture_manager.h"
#include "../DTO/common_objetoDTO.h"
#include "explotion.h"
#include "../DTO/common_provisionDTO.h"


#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>

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
    void renderizar_viga(VigaDTO viga); // 140 20 70 20
    void renderizar_provision(ProvisionDTO provision);
    void centrarEnGusano(int x, int y);
    void renderizar_gusano(JugadorDTO jugador);
    void renderizar_fondo_pantalla();
    void reproducir_musica();
    void renderizar_misil(ObjetoDTO objeto);
    void reproducir_efecto_salto();
    void mutear_sonidos();
    void reproducir_efecto(std::string path_efecto);
    void reproducir_efecto_arma(int tipo);
    void renderizar_municion(JugadorDTO& jugador);
    void renderizar_explocion(Explotion& explotion);
    void reproducir_sonido_explosion();
};

#endif // VIEW_H
