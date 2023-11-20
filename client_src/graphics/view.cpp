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


	//std::shared_ptr<SDL2pp::Texture> background = tex_manager.getBackground();
  // Definir el rectángulo de destino para que coincida con las dimensiones de la pantalla
  	//renderer.Copy(*background, NullOpt, Rect(0, 0, window.GetWidth(), window.GetHeight()));
    



}

void GameView::renderizar_texto(std::string texto, int pos_x, int pos_y, SDL_Color color)
{
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 12);

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

void GameView::centrarEnGusano(int x, int y)
{
    // // Calcula la posición centrada de la vista basada en la posición del gusano
    // int viewX = x - window.GetWidth() / 2;
    // int viewY = y - window.GetHeight() / 2;

    // // Asegúrate de que la vista no se salga del escenario (ajustar según tus necesidades)
    // if (viewX < 0) viewX = 0;
    // if (viewY < 0) viewY = 0;
    // // Puedes ajustar estos límites según las dimensiones de tu escenario

    // // Mueve la ventana a la posición centrada
    // window.SetPosition(viewX, viewY);
    //SDL2pp::Rect camera(0, 0, window.GetWidth(), window.GetHeight());
    //camera.x = x;
    //camera.y = 200-y;

    // Luego, aplicas la cámara antes de renderizar
    //renderer.SetViewport(camera);
}

// con el for agarra el jugador y se lo manda a render y renderiza
void GameView::renderizar_gusano(JugadorDTO jugador)
{
    std::string vida_string = std::to_string(jugador.obtener_vida());
    std::string texto = "Vida:" + vida_string;
    SDL_Color color = jugador.obtener_color();
    renderizar_texto(texto, jugador.posicion_x(), 200-jugador.posicion_y(), color);
    jugador.renderizar(renderer, tex_manager);//paso renderer y text_manager
}

void GameView::renderizar_viga(VigaDTO viga)
{
    viga.renderizar(renderer, tex_manager);//paso renderer y text_manager
   
}

void GameView::reproducir_musica()
{   
    std::shared_ptr<SDL2pp::Music> music = tex_manager.getMusic();
    //mixer.PlayMusic(*music, -1);
}


void GameView::renderizar_misil(ObjetoDTO objeto){


    // Debo tener el arma el game
    objeto.renderizar(renderer, tex_manager);

}