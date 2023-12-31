
#ifndef VIEW_H
#define VIEW_H
#include <map>
#include <string>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include "../DTO/common_jugadorDTO.h"
#include "../DTO/common_vigaDTO.h"
#include "texture_manager.h"
#include "../DTO/common_objetoDTO.h"
#include "../DTO/common_vientoDTO.h"
#include "explotion.h"
#include "team_health.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>

#define FONDO_DIA 1
#define FONDO_NIEVE 2
#define FONDO_NOCHE 3

class GameView
{

private: 
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SDL2pp::SDLTTF ttf; // para render de letra
    SDL2pp::Mixer mixer;
    std::shared_ptr<SDL2pp::Chunk> sonido_actual;
	int canal_anterior;

    TextureManager tex_manager;

    void renderizar_viento_derecha(int x, int y, int ancho);
    void renderizar_viento_izquierda(int x, int y, int ancho);
public:
    explicit GameView();

    void mostrar();
    void clear();
    SDL2pp::Renderer &getRenderer();
    void renderizar_texto(const std::string texto, int pos_x, int pos_y, SDL_Color color, int font_size);
    void renderizar_viga(VigaDTO viga);
    void renderizar_gusano(JugadorDTO jugador);
    void renderizar_fondo_pantalla(int tipo_fondo);
    void reproducir_musica();
    void renderizar_misil(ObjetoDTO objeto);
    void reproducir_efecto_salto();
    void mutear_sonidos();
    void reproducir_efecto(std::string path_efecto);
    void reproducir_efecto_arma(int tipo);
    void renderizar_municion(JugadorDTO& jugador);
    void renderizar_explocion(Explotion& explotion);
    void reproducir_sonido_explosion();
    void renderizar_viento(VientoDTO &viento);
    void renderizar_end_game(bool ganaste);
    void renderizar_vida_por_equipos(TeamHealth &team_health);
};

#endif // VIEW_H
