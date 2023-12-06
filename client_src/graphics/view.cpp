#include "view.h"

#include <iostream>
GameView::GameView() : sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO), window("Worms", SDL_WINDOWPOS_UNDEFINED,
                                                                    SDL_WINDOWPOS_UNDEFINED, 640, 480, 0),
                       renderer(window, -1, SDL_RENDERER_ACCELERATED),
                       mixer(MIX_DEFAULT_FREQUENCY, 0x8010, 2, 4096),
                       canal_anterior(-1)
{
    tex_manager.loadTexture(this->renderer);   
    tex_manager.loadBackground(this->renderer); 
    tex_manager.loadBackgroundNight(this->renderer);
    tex_manager.loadBackgroundSnow(this->renderer);
    tex_manager.loadWater(this->renderer);
    tex_manager.loadMusic();
    tex_manager.loadSounds();
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

void GameView::renderizar_fondo_pantalla(int tipo_fondo)
{

    std::shared_ptr<SDL2pp::Texture> background;
    if (tipo_fondo == FONDO_NOCHE)
    {
        background = tex_manager.getBackgroundNight();
    }
    else if (tipo_fondo == FONDO_NIEVE)
    {
        background = tex_manager.getBackgroundSnow();
    }
    else
    {
        background = tex_manager.getBackground();
    }
    renderer.Copy(*background, SDL2pp::NullOpt, SDL2pp::Rect(0, 0, window.GetWidth(), window.GetHeight()));
    std::shared_ptr<SDL2pp::Texture> water = tex_manager.getWater();
    renderer.Copy(*water, SDL2pp::NullOpt, SDL2pp::Rect(0, 200, window.GetWidth(), window.GetHeight() - 100));
}

void GameView::renderizar_texto(std::string texto, int pos_x, int pos_y, SDL_Color color, int font_size)
{
    SDL2pp::Font font(DATA_PATH "/GROBOLD.ttf", font_size);

    SDL2pp::Texture texto_sprite(renderer, font.RenderText_Blended(texto, color));

    int textWidth = texto_sprite.GetWidth();
    int textHeight = texto_sprite.GetHeight();

    int adjustedPosX = pos_x; 
    int adjustedPosY = pos_y; 

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


void GameView::renderizar_gusano(JugadorDTO jugador)
{
    std::string vida_string = std::to_string(jugador.obtener_vida());
    std::string texto = "Vida:" + vida_string;
    SDL_Color color = jugador.obtener_color();
    renderizar_texto(texto, jugador.posicion_x(), 200 - jugador.posicion_y(), color, 12);
    jugador.renderizar(renderer, tex_manager); 
}

void GameView::renderizar_viga(VigaDTO viga)
{
    viga.renderizar(renderer, tex_manager);
}

void GameView::reproducir_musica()
{
    std::shared_ptr<SDL2pp::Music> music = tex_manager.getMusic();
    mixer.SetMusicVolume(9);
    mixer.PlayMusic(*music, -1);
}

void GameView::renderizar_misil(ObjetoDTO objeto)
{
    objeto.renderizar(renderer, tex_manager);
}

void GameView::reproducir_efecto(std::string path_efecto)
{
    this->sonido_actual = tex_manager.getSound(path_efecto);

    if (this->canal_anterior != -1)
        mixer.HaltChannel(this->canal_anterior);

    if (this->sonido_actual)
        this->canal_anterior = mixer.PlayChannel(-1, *(this->sonido_actual), 0);
    else
        this->canal_anterior = -1;
}

void GameView::reproducir_efecto_arma(int tipo)
{
    if (tipo == AIR_STRIKE)
    {
        reproducir_efecto("/sonidos/ataque misiles.wav");
    }
    else if (tipo == TELEPORT)
    {
        reproducir_efecto("/sonidos/teletransportar.WAV");
    }
    else if (tipo == BAT)
    {
        reproducir_efecto("/sonidos/bate.wav");
    }
    else if (tipo == BAZOOKA or tipo == MORTAR)
    {
        reproducir_efecto("/sonidos/lanzarmisil.WAV");
    }
}

void GameView::reproducir_sonido_explosion()
{
    reproducir_efecto("/sonidos/Explosion1.wav");
}

void GameView::mutear_sonidos()
{
    mixer.PauseMusic();
}

void GameView::renderizar_municion(JugadorDTO &jugador)
{
    int municion = jugador.obtenerMunicion();
    std::string texto = "Municion: " + ((municion < 0) ? "Infinita" : std::to_string(municion));
    SDL_Color color = {255, 255, 255, 255};
    this->renderizar_texto(texto, 0, 10, color, 12);
}

void GameView::renderizar_explocion(Explotion &explotion)
{
    explotion.renderizar(renderer, tex_manager);
    // se actualiza sola (?
}

void GameView::renderizar_viento(VientoDTO &viento)
{

    // renderizo un rectangulo negro
    int x = 400, y = 400;
    std::string path = "/misc/windback.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    this->renderer.Copy(
        *texture,
        SDL2pp::Rect(0, 0, 195, 15),        
        SDL2pp::Rect(x + 3, y - 1, 195, 17), 
        0,                                   
        SDL2pp::NullOpt,                     
        SDL_FLIP_NONE                        
    );

    int velocidad = viento.obtenerVelocidad();
    if (velocidad == 0)
    {
        return;
    }

    bool direccion = viento.obtenerDireccion();
    int ancho = (velocidad * 100) / VELOCIDAD_MAXIMA_VIENTO; 

    if (ancho > 100)
    {
        ancho = 100;
    }

    if (direccion)
    {
        this->renderizar_viento_derecha(x + 100, y, ancho);
    }
    else
    {
        this->renderizar_viento_izquierda(x + 100, y, ancho);
    }
}

void GameView::renderizar_viento_derecha(int x, int y, int ancho)
{
    int src_x = (ancho) > 96 ? 96 : ancho;

    std::string path = "/misc/windr.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    this->renderer.Copy(
        *texture,
        SDL2pp::Rect(0, 0, src_x, 13),     
        SDL2pp::Rect(x + 1, y, src_x, 15), 
        0,                                 
        SDL2pp::NullOpt,                   
        SDL_FLIP_NONE                     
    );
}

void GameView::renderizar_viento_izquierda(int x, int y, int ancho)
{
    int src_x = (ancho) > 96 ? 96 : ancho;
    std::string path = "/misc/windl.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    this->renderer.Copy(
        *texture,
        SDL2pp::Rect(0, 0, src_x, 13),        
        SDL2pp::Rect(x - src_x, y, src_x, 15), 
        0,                                    
        SDL2pp::NullOpt,                       
        SDL_FLIP_NONE                         
    );
}

void GameView::renderizar_end_game(bool ganaste)
{

    std::string path = "/misc/box.png";

    int x = renderer.GetOutputWidth() / 2 - 150;
    int y = renderer.GetOutputHeight() / 2 - 100;
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);
    this->renderer.Copy(
        *texture,
        SDL2pp::Rect(0, 0, 195, 15),  
        SDL2pp::Rect(x, y, 300, 100), 
        0,                            
        SDL2pp::NullOpt,              
        SDL_FLIP_NONE                 
    );

    std::string resultado;
    SDL_Color color = {255, 255, 255, 255};

    int pos_x, pos_y;
    if (ganaste)
    {
        resultado = "Ganaste!";
        pos_x = x + 80;
        pos_y = y + 35;
    }
    else
    {
        resultado = "Perdiste";
        pos_x = x + 90;
        pos_y = y + 40;
    }

    this->renderizar_texto(resultado, pos_x, pos_y, color, 30);
}

void GameView::renderizar_vida_por_equipos(TeamHealth &team_health)
{

    const std::map<int, int> &vida_por_equipo = team_health.obtenerVida();
    const std::map<int, SDL_Color> &color_por_equipo = team_health.obtenerColores();

    int pos_x = 10;
    int pos_y = renderer.GetOutputHeight() / 2 + 100;

    std::string texto = "Jugadores";
    SDL_Color color_texto = {255, 255, 255, 255};
    this->renderizar_texto(texto, pos_x, pos_y, color_texto, 14);
    // Jugador <id> : >vida>
    for (auto const &[id, vida] : vida_por_equipo)
    {
        std::string vida_jugador = "Jugador " + std::to_string(id) + ": " + std::to_string(vida);
        SDL_Color color = color_por_equipo.at(id);
        this->renderizar_texto(vida_jugador, pos_x, pos_y + id * 14, color, 12);
    }
}
