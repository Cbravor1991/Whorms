#include "view.h"

#include <iostream>
GameView::GameView() : sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO), window("Worms", SDL_WINDOWPOS_UNDEFINED,
                                                                    SDL_WINDOWPOS_UNDEFINED, 640, 480, 0),
                       renderer(window, -1, SDL_RENDERER_ACCELERATED),
                       mixer(MIX_DEFAULT_FREQUENCY, 0x8010, 2, 4096),
                       canal_anterior(-1)
{
    tex_manager.loadTexture(this->renderer);    // carga las texturas de los sprites
    tex_manager.loadBackground(this->renderer); // carga la texturas del fondo
    tex_manager.loadBackgroundNight(this->renderer);
    tex_manager.loadBackgroundSnow(this->renderer);
    tex_manager.loadWater(this->renderer);
    tex_manager.loadMusic(); // carga una cancion
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

void GameView::renderizar_fondo_pantalla(std::string fondo_seleccionado)
{

    std::shared_ptr<SDL2pp::Texture> background = tex_manager.getBackground();
    if (fondo_seleccionado == "noche")
    {
        background = tex_manager.getBackgroundNight();
    }
    if (fondo_seleccionado == "snow")
    {
        background = tex_manager.getBackgroundSnow();
    }
    renderer.Copy(*background, NullOpt, Rect(0, 0, window.GetWidth(), window.GetHeight()));
    std::shared_ptr<SDL2pp::Texture> water = tex_manager.getWater();
    renderer.Copy(*water, NullOpt, Rect(0, 200, window.GetWidth(), window.GetHeight() - 100));
}

void GameView::renderizar_texto(std::string texto, int pos_x, int pos_y, SDL_Color color)
{
    SDL2pp::Font font(DATA_PATH "/GROBOLD.ttf", 12);

    SDL2pp::Texture texto_sprite(renderer, font.RenderText_Blended(texto, color));

    int textWidth = texto_sprite.GetWidth();
    int textHeight = texto_sprite.GetHeight();

    // Ajustar la posición y tamaño del texto según el tamaño de la ventana
    int adjustedPosX = pos_x; // Puedes ajustar esto según tus necesidades
    int adjustedPosY = pos_y; // Puedes ajustar esto según tus necesidades

    // Asegurarse de que el texto no se salga de la pantalla
    if (adjustedPosX + textWidth > window.GetWidth())
    {
        adjustedPosX = window.GetWidth() - textWidth;
    }

    if (adjustedPosY + textHeight > window.GetHeight())
    {
        adjustedPosY = window.GetHeight() - textHeight;
    }

    renderer.Copy(texto_sprite, SDL2pp::NullOpt,
                  SDL2pp::Rect(adjustedPosX, adjustedPosY, textWidth, textHeight));
}

void GameView::renderizar_objeto(Objeto objeto, int id_objeto_seleccionado)
{
    objeto.renderizar(renderer, tex_manager, id_objeto_seleccionado);
}

void GameView::reproducir_musica()
{
    std::shared_ptr<SDL2pp::Music> music = tex_manager.getMusic();
    mixer.SetMusicVolume(9);
    mixer.PlayMusic(*music, -1);
}

void GameView::mutear_sonidos()
{
    mixer.PauseMusic();
}
