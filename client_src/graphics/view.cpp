#include "view.h"

#include <iostream>
GameView::GameView() : sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO), window("Worms", SDL_WINDOWPOS_UNDEFINED,
                                                   SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE),
                       renderer(window, -1, SDL_RENDERER_ACCELERATED),
                       mixer(MIX_DEFAULT_FREQUENCY, 0x8010, 2, 4096)
{
    tex_manager.loadTexture(this->renderer);//carga las texturas de los sprites
    tex_manager.loadBackground(this->renderer);//carga la texturas del fondo
    tex_manager.loadMusic();//carga una cancion
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


void GameView::renderizar_fondo_pantalla(){


	std::shared_ptr<SDL2pp::Texture> background = tex_manager.getBackground();
  // Definir el rectángulo de destino para que coincida con las dimensiones de la pantalla
  	renderer.Copy(*background, NullOpt, Rect(0, 0, window.GetWidth(), window.GetHeight()));
    



}

void GameView::renderizar_texto(std::string texto, int pos_x, int pos_y)
{
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 12);

    SDL_Color color = {255, 255, 255, 255};
    SDL2pp::Texture texto_sprite(renderer, font.RenderText_Blended(texto, color));

    int textWidth = texto_sprite.GetWidth();
    int textHeight = texto_sprite.GetHeight();

    // Ajustar la posición y tamaño del texto según el tamaño de la ventana
    int adjustedPosX = pos_x; // Puedes ajustar esto según tus necesidades
    int adjustedPosY = pos_y; // Puedes ajustar esto según tus necesidades

    // Asegurarse de que el texto no se salga de la pantalla
    if (adjustedPosX + textWidth > window.GetWidth()) {
        adjustedPosX = window.GetWidth() - textWidth;
    }

    if (adjustedPosY + textHeight > window.GetHeight()) {
        adjustedPosY = window.GetHeight() - textHeight;
    }

    renderer.Copy(texto_sprite, SDL2pp::NullOpt,
                  SDL2pp::Rect(adjustedPosX, adjustedPosY, textWidth, textHeight));

}

// con el for agarra el jugador y se lo manda a render y renderiza
void GameView::renderizar_gusano(JugadorDTO jugador)
{
    jugador.renderizar(renderer, tex_manager);//paso renderer y text_manager
  
}

void GameView::renderizar_viga(VigaDTO viga)
{
    viga.renderizar(renderer, tex_manager);//paso renderer y text_manager
   
}

void GameView::reproducir_musica()
{   
    std::shared_ptr<SDL2pp::Music> music = tex_manager.getMusic();
    mixer.PlayMusic(*music, -1);
}
