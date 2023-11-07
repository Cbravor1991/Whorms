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

    StateGame *estado;
    while (cliente.esta_conectado())
    {
        bool nuevo_estado = false;
        uint32_t ticks = SDL_GetTicks();

        std::optional<StateGame *> optional = cliente.obtener_estado();
        if (optional.has_value())
        {
            estado = optional.value();
            nuevo_estado = true;
        }

        if (not this->gameLoop(estado, nuevo_estado))
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

bool Game::gameLoop(StateGame *estado, bool &nuevo_estado)
{   
    view.clear();
    //estado->cambiar_render(permiso); -->para debuggear si llega algo no definido en procesar
    if(nuevo_estado) {
        this->procesar_estado(estado);
    }

    
    this->renderizar();
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

void Game::procesar_estado(StateGame* estado) {

    if(estado->type == TIPO_TURNO) {
        TurnoDTO* turn = dynamic_cast<TurnoDTO*> (estado);
        this->turno = turn->obtenerIdTurno();
        permiso = turn->obtenerPermiso();
        cliente.autorizar_turno(permiso);

    }else if(estado->type == TIPO_SEGUNDO) {
        SegundosDTO* segundos = dynamic_cast<SegundosDTO*> (estado);
        this->tiempo_restante_turno = segundos->obtenerTiempo();

    } else if (estado->type == TIPO_PAQUETE) {
        PaqueteDTO* paquete = dynamic_cast<PaqueteDTO*> (estado);
        this->procesar_paquete(paquete);
        
    } else if(estado->type == TIPO_ESCENARIO) {
        EscenarioDTO* escenario = dynamic_cast<EscenarioDTO*>(estado);
        this->cargar_escenario(escenario);
    }
}


void Game::procesar_paquete(PaqueteDTO* paquete) {

    std::vector<JugadorDTO> jugadores_paquete = paquete->obtener_jugadores();

    for (auto & jugador_ : jugadores_paquete){

        JugadorDTO jugador = jugador_;

        int id = jugador.obtenerId();
        if (jugadores.find(id) == jugadores.end()) {
            // not found --> lo guardo
            jugadores.emplace(std::make_pair(id, jugador));
        } else {
            //found --> lo actualizo o borro si se desconecto(no recibo esta info)
            jugadores.at(id).actualizar(jugador);
        }
    }     
}

void Game::cargar_escenario(EscenarioDTO* escenario) {
    std::vector<VigaDTO> vigas_escenario = escenario->obtener_vigas();

    for (VigaDTO viga : vigas_escenario)
        {
            vigas.push_back(viga);
        }
    
}

void Game::renderizar() {

    std::string time = "Tiempo restante: " + std::to_string((tiempo_restante_turno)) + 
                        " Es mi turno: " + (permiso ? "true" : "false");

    view.renderizar_texto(time, 0, 0);
    //view.renderizar_gusano(0,0);




    // for(VigaDTO viga : vigas) { //para mostrar las vigas
    //     //viga.mostrar();//renderizo la viga
    // }

    for (auto const& [id, jugador] : jugadores){//para mostrar los jugadores
        jugador.mostrar();
    }

    view.mostrar();

}

