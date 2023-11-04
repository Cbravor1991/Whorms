#include "view.h"

#include <iostream>
GameView::GameView(): sdl(SDL_INIT_VIDEO), window("Worms",SDL_WINDOWPOS_UNDEFINED, 
                        SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE),
                        renderer(window, -1, SDL_RENDERER_ACCELERATED)
{
    renderer.SetDrawColor(100, 149, 237, 0);//seteo el color de fondo
}

    
void GameView::mostrar() {
    renderer.Present();
}
void GameView::clear() {
    renderer.Clear();
}

SDL2pp::Renderer& GameView::getRenderer() {
    return this->renderer;
}
