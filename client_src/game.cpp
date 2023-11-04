#include "game.h"

#include <SDL2pp/SDL2pp.hh>


Game::Game(const std::string &hostname, const std::string &servname): 
            cliente(hostname, servname) {}


void Game::run() {

    bool permiso = false;
    StateGame *estado;
    while (cliente.esta_conectado()) {
        uint32_t ticks = SDL_GetTicks();//

        //StateGame *estado = cliente.obtener_estado();
        std::optional<StateGame*> optional = cliente.obtener_estado();
        if (optional.has_value()) {
            estado = optional.value();
        }

        if (not this->gameLoop(estado, permiso) ) {
            break;
        }

        uint32_t frame_ticks = SDL_GetTicks();//
        uint32_t tick_diff = frame_ticks - ticks;//
        if(tick_diff <= 300) {//
            SDL_Delay(300 - tick_diff);//
        } else {
            //retraso todo?
        }
    }
}

bool Game::gameLoop(StateGame *estado, bool &permiso) {
    view.clear();
    //obtiene los datos y manda a renderizarlos
    //maneja los eventos(y envia a cola del sender si hay alguno para que los procese)

    estado->cambiar_render(permiso);//rompe cuando no hay estado

    cliente.autorizar_turno(permiso);
    view.mostrar();//muestra todo por pantalla
    return this->manejarEventos();
}

bool Game::manejarEventos() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

                case(SDLK_LEFT): {
                    cliente.mover_izquierda();
                    break;
                }
                
                case(SDLK_RIGHT): {
                    cliente.mover_derecha();
                    break;
                }
                
                case(SDLK_RETURN): {//Enter
                    cliente.saltar_hacia_delante();
                    break;
                }
                case(SDLK_BACKSPACE): {//Retorno
                    cliente.saltar_hacia_atras();
                    break;
                }
                default: {
                    //si llego aca, es una tecla que no uso
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