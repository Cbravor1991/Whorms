#include "game.h"

#include <SDL2pp/SDL2pp.hh>

#define FRAME_RATE 30 // Aumentar si queres que no salgan muchos mensajes en la terminal
                      // pero, la pantalla se va a renderizar más lento y hace mas lento
                      // el recibir cosas del servidor por lo que genera lag
                      // Valor original = 30

const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_DERECHA = 2;
const int MOVIMIENTO_ARRIBA_ADELANTE = 3;
const int MOVIMIENTO_ARRIBA_ATRAS = 4;

Game::Game(const std::string &hostname, const std::string &servname) : cliente(hostname, servname) {}

void Game::run()
{

    bool permiso = false;
    StateGame *estado;
    while (cliente.esta_conectado())
    {
        uint32_t ticks = SDL_GetTicks();

        std::optional<StateGame *> optional = cliente.obtener_estado();
        if (optional.has_value())
        {
            estado = optional.value();
        }

        if (not this->gameLoop(estado, permiso))
        {
            break;
        }

        uint32_t frame_ticks = SDL_GetTicks();
        uint32_t tick_diff = frame_ticks - ticks;
        if (tick_diff <= FRAME_RATE)
        { //
            SDL_Delay(FRAME_RATE - tick_diff);
        }
        else
        {
            // retraso todo?
        }
    }
}

bool Game::gameLoop(StateGame *estado, bool &permiso)
{
    view.clear();

    estado->cambiar_render(permiso);
    cliente.autorizar_turno(permiso);

    view.mostrar();
    return this->manejarEventos();
}

bool Game::manejarEventos()
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {

            case (SDLK_LEFT):
            {
                cliente.mover(MOVIMIENTO_IZQUIERDA);
                break;
            }

            case (SDLK_RIGHT):
            {
                cliente.mover(MOVIMIENTO_DERECHA);
                break;
            }

            case (SDLK_RETURN):
            { // Enter
                cliente.mover(MOVIMIENTO_ARRIBA_ADELANTE);
                break;
            }
            case (SDLK_BACKSPACE):
            { // Retorno
                cliente.mover(MOVIMIENTO_ARRIBA_ATRAS);
                break;
            }
            default:
            {
                // si llego aca, es una tecla que no uso
                std::cout << "Key=" << event.key.keysym.sym << "\n";
                break;
            }
            }
            // } else if(event.type == SDL_KEYUP) {
            //     cliente.stop();//para de moverse(la animacion)
        }
    }
    return true;
}