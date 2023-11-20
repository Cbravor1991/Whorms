#include "game.h"

#include <SDL2pp/SDL2pp.hh>

#define FRAME_RATE 4.0f / 70.0f // Aumentar si queres que no salgan muchos mensajes en la terminal
                                // pero, la pantalla se va a renderizar más lento y hace mas lento
                                // el recibir cosas del servidor por lo que genera lag
                                // Valor original = 30

Game::Game(const std::string &hostname, const std::string &servname) : cliente(hostname, servname) {}

void Game::run()
{

    StateGame *estado;
    view.reproducir_musica();
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
    // estado->cambiar_render(permiso); -->para debuggear si llega algo no definido en procesar
    if (nuevo_estado)
    {
        this->procesar_estado(estado);
    }

    this->renderizar();
    view.mostrar();




 
    return this->manejarEventos();
}

bool Game::manejarEventos()
{
    Action *accion = nullptr;
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

            case (SDLK_r):
            {
                
                tipo++;

                if (tipo>2){
                    tipo = 0;
                }

                accion = new Weapon(tipo);
                cliente.mandar_accion(accion);
                break;
            }
            case (SDLK_LEFT):
            {
                accion = new Left();
                cliente.mandar_accion(accion);
                break;
            }

            case (SDLK_RIGHT):
            {
                accion = new Right();
                cliente.mandar_accion(accion);
                break;
            }

            case (SDLK_RETURN):
            { // Enter
                accion = new JumpFoward();
                cliente.mandar_accion(accion);
                break;
            }
            case (SDLK_BACKSPACE):
            { // Retorno
                accion = new JumpBack();
                cliente.mandar_accion(accion);
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
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                // Se ha hecho clic con el botón izquierdo del ratón
                int mouseX = event.button.x;
                int mouseY = 200 - event.button.y;

                // Ahora puedes usar las variables mouseX y mouseY según tus necesidades
                std::cout << "Clic en la posición X: " << mouseX << ", Y: " << mouseY << std::endl;
                accion = new Position(mouseX, mouseY);
                cliente.mandar_accion(accion);
            }
        }
    }
    return true;
}

void Game::procesar_estado(StateGame *estado)
{

    if (estado->type == TIPO_TURNO)
    {
        TurnoDTO *turn = dynamic_cast<TurnoDTO *>(estado);
        this->turno = turn->obtenerIdTurno();
        permiso = turn->obtenerPermiso();
        cliente.autorizar_turno(permiso);
    }
    else if (estado->type == TIPO_SEGUNDO)
    {
        SegundosDTO *segundos = dynamic_cast<SegundosDTO *>(estado);
        this->tiempo_restante_turno = segundos->obtenerTiempo();
    }
    else if (estado->type == TIPO_PAQUETE)
    {
        PaqueteDTO *paquete = dynamic_cast<PaqueteDTO *>(estado);
        this->procesar_paquete(paquete);
    }
    else if (estado->type == TIPO_ESCENARIO)
    {
        EscenarioDTO *escenario = dynamic_cast<EscenarioDTO *>(estado);
        this->cargar_escenario(escenario);
    }
    else if (estado->type == TIPO_ARMA)
    {
        ArmaDTO *arma = dynamic_cast<ArmaDTO *>(estado);
        arma->cargar(jugadores);
      
          
        

    }
}

void Game::procesar_paquete(PaqueteDTO *paquete)
{

    std::vector<JugadorDTO> jugadores_paquete = paquete->obtener_jugadores();
    std::set<int> jugadores_en_paquete;
    for (auto &jugador_ : jugadores_paquete)
    {

        JugadorDTO jugador = jugador_;

        gusanoX = jugador.posicion_x();
        gusanoY = jugador.posicion_y();

        int id = jugador.obtenerId();
        jugadores_en_paquete.insert(id);
        if (jugadores.find(id) == jugadores.end())
        {
            // not found --> lo guardo
            jugadores.emplace(std::make_pair(id, jugador));
        }
        else
        {
            // found --> lo actualizo o borro si se desconecto(no recibo esta info)
            jugadores.at(id).actualizar(jugador);
        }
        if (id == turno)
        {
            jugadores.at(id).activa_animacion(true);
        }
        else
        {
            jugadores.at(id).activa_animacion(false);
        }
    }
    for (auto it = jugadores.begin(); it != jugadores.end();)
    {
        if (jugadores_en_paquete.find(it->first) == jugadores_en_paquete.end())
        {
            it = jugadores.erase(it);
        }
        else
        {
            ++it;
        }
    }

   std::vector<ObjetoDTO> objetos_paquete = paquete->obtener_objetos();

   int tamaño_paquete = static_cast<int>(objetos_paquete.size());
   int cantidad_misiles = static_cast<int>(objetos.size());

    //std::set<int> jugadores_en_paquete;

    if(objetos.size()> objetos_paquete.size()){
        int misiles_destruidos = objetos.size()-objetos_paquete.size();

        objetos.erase(objetos.begin(), objetos.begin() + misiles_destruidos);


    }

    if (tamaño_paquete>0){
      
           for (int i = 0; i < tamaño_paquete; ++i) {
    std::cout << "estoy creando" << '\n';

    if (i >= cantidad_misiles) {
        std::cout << "estoy creando" << '\n';
        // No se encontró el índice en "objetos" --> lo guardo
        objetos.push_back(objetos_paquete.at(i));
    } else {
        // Verificar que objetos.at(i) esté dentro del rango válido
        if (i < cantidad_misiles) {
            objetos.at(i).actualizar(objetos_paquete.at(i));
        } else {
            // Manejar el caso donde i es mayor que el tamaño de "objetos"
            // Esto podría ser un error o requerir alguna lógica adicional según tus necesidades
            std::cerr << "Error: Índice fuera de rango en 'objetos'." << std::endl;
        }
    }
}

       
    }


       

}

void Game::cargar_escenario(EscenarioDTO *escenario)
{
    std::vector<VigaDTO> vigas_escenario = escenario->obtener_vigas();

    for (VigaDTO viga : vigas_escenario)
    {
        vigas.push_back(viga);
    }
}

void Game:: cargar_arma (PaqueteDTO *paquete){

    std::cout<<"entra aca"<<'\n';
   

}

void Game::renderizar()
{
    // Centra la vista en la posición actual del gusano
    view.centrarEnGusano(gusanoX, gusanoY);

    std::string time = "Tiempo restante: " + std::to_string((tiempo_restante_turno)) +
                       " Es mi turno: " + (permiso ? "true" : "false");

    view.renderizar_fondo_pantalla();
    SDL_Color color = {255, 255, 255, 255};
    view.renderizar_texto(time, 0, 0, color);
    // view.renderizar_gusano(0,0);

    for (VigaDTO viga : vigas)
    { // para mostrar las vigas
        view.renderizar_viga(viga);
    }

    for (auto const &[id, jugador] : jugadores)
    { // para mostrar los jugadores

        view.renderizar_gusano(jugador);
    }

           
        this->renderizar_misiles();

    view.mostrar();
}


void Game::renderizar_misiles(){
   
    
    for (ObjetoDTO misil : objetos)
    { // para mostrar las vigas
            view.renderizar_misil(misil);
    }
}