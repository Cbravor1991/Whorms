#include "view.h"

#include <iostream>
GameView::GameView() : sdl(SDL_INIT_VIDEO), window("Worms", SDL_WINDOWPOS_UNDEFINED,
                                                   SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE),
                       renderer(window, -1, SDL_RENDERER_ACCELERATED)
{
    renderer.SetDrawColor(100, 149, 237, 0); // seteo el color de fondo
}

void GameView::mostrar()
{
    renderer.Present();
}
void GameView::clear()
{
    renderer.Clear();
}

SDL2pp::Renderer &GameView::getRenderer()
{
    return this->renderer;
}

void GameView::renderizar_texto(std::string texto, int pos_x, int pos_y)
{

    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 12);

    SDL2pp::Texture texto_sprite(
        renderer,
        font.RenderText_Blended(texto, SDL_Color{255, 255, 255, 255}));

    renderer.Copy(texto_sprite, SDL2pp::NullOpt,
                  SDL2pp::Rect(0, 0, texto_sprite.GetWidth(), texto_sprite.GetHeight()));
}

// con el for agarra el jugador y se lo manda a render y renderiza
void GameView::renderizar_gusano(JugadorDTO jugador)
{
    jugador.renderizar(renderer);
}

void GameView::renderizar_viga(VigaDTO viga)
{
    viga.renderizar(renderer);
}
