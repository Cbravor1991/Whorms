#include "game.h"

#include <SDL2pp/SDL2pp.hh>

#define SLEEP_RATE (4.0f / 35.0f) * 50

Game::Game() {
    tipos_objetos.push_back("Gusano");
    tipos_objetos.push_back("Viga larga 45°");
    tipos_objetos.push_back("Viga larga -45°");
    tipos_objetos.push_back("Viga larga 0°");
    tipos_objetos.push_back("Viga corta 45°");
    tipos_objetos.push_back("Viga corta -45°");
    tipos_objetos.push_back("Viga corta 0°");
    tipos_objetos.push_back("Borrar");
}

void Game::crear_mapa(std::string fondo_seleccionado, std::string nombre_mapa_recibido)
{   nombre_mapa = nombre_mapa_recibido;
    fondo_eleguido = fondo_seleccionado;
    view.reproducir_musica();
    uint32_t timeLost = 0;
    while (true)
    {
        uint32_t ticks = SDL_GetTicks();
        if (not this->gameLoop())
        {
            break;
        }
        uint32_t frame_ticks = SDL_GetTicks();
        uint32_t tick_diff = (frame_ticks - ticks) - timeLost;
        if (tick_diff <= SLEEP_RATE)
        {
            SDL_Delay(SLEEP_RATE - tick_diff);
            timeLost = SLEEP_RATE - tick_diff;
        }
        else
        {
            timeLost = 0;
        }
    }
   
}

bool Game::gameLoop()
{
    view.clear();
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
            case (SDLK_r):
            {   
                contador_objetos++;
                if (contador_objetos < cantidad_objetos) {
                    this->objeto_renderizar = tipos_objetos.at(contador_objetos);
                } else {
                    contador_objetos = -1;
                }
                break;
            }
            case (SDLK_t):
            {
                std::cout << "t" << std::endl;
                break;
            }
            case (SDLK_q):
            {
                std::cout << "q" << std::endl;
                break;
            }  case (SDLK_m):
            {
                  view.mutear_sonidos();
                
                break;
            }
            case (SDLK_RETURN):
            { // Enter
                guardar_datos();
                break;
            }
        
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = 200 - event.button.y;
                std::cout << "Clic en la posición X: " << mouseX << ", Y: " << mouseY << std::endl;
                if (this->objeto_renderizar == "Viga corta 45°") {
                    Objeto viga(0, mouseX, mouseY, 45);
                    objetos_creados.push_back(viga);
                } else if (this->objeto_renderizar == "Gusano") {
                    Objeto gusano(2, mouseX, mouseY, 0);
                    objetos_creados.push_back(gusano);
                    spawns_automaticos = false;
                } else if (this->objeto_renderizar == "Viga corta -45°") {
                    Objeto viga(0, mouseX, mouseY, -45);
                    objetos_creados.push_back(viga);
                } else if (this->objeto_renderizar == "Viga corta 0°") {
                    Objeto viga(0, mouseX, mouseY, 0);
                    objetos_creados.push_back(viga);
                } else if (this->objeto_renderizar == "Viga larga 45°") {
                    Objeto viga(1, mouseX, mouseY, 45);
                    objetos_creados.push_back(viga);
                } else if (this->objeto_renderizar == "Viga larga 0°") {
                    Objeto viga(1, mouseX, mouseY, 0);
                    objetos_creados.push_back(viga);
                } else if (this->objeto_renderizar == "Viga larga -45°") {
                    Objeto viga(1, mouseX, mouseY, -45);
                    objetos_creados.push_back(viga);
                }
            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                int mouseX = event.button.x;
                int mouseY = 200 - event.button.y;

                auto it = std::remove_if(objetos_creados.begin(), objetos_creados.end(),
                                         [mouseX, mouseY](const Objeto &objeto)
                                         {
                                             return mouseX == objeto.getX() && mouseY == objeto.getY();
                                         });

                objetos_creados.erase(it, objetos_creados.end());
            }
        }
    
    }
    return true;
}

void Game::guardar_datos() {
    YAML::Node nodoPrincipal;

    nodoPrincipal["fondo"]["pantalla"] = 0;

    if (spawns_automaticos) {
        nodoPrincipal["spawns_automaticos"] = 1;
    } else {
        nodoPrincipal["spawns_automaticos"] = 0;
    }

    YAML::Node nodoVigas;
    YAML::Node nodoSpawns;

    for (const auto& objeto : objetos_creados) {
        YAML::Node nodoViga;
        YAML::Node nodoSpawn;
        if (objeto.getTipo() == 2) {
            nodoSpawn["x"] = objeto.getX();
            nodoSpawn["y"] = objeto.getY();
            nodoSpawns.push_back(nodoSpawn);
        } else {
            nodoViga["tipo"] = objeto.getTipo() ? 1 : 0;
            nodoViga["x"] = objeto.getX();
            nodoViga["y"] = objeto.getY();
            nodoViga["angulo"] = objeto.getAngulo();
            nodoVigas.push_back(nodoViga);
        }
    }
    nodoPrincipal["spawns_mapa"] = nodoSpawns;
    nodoPrincipal["vigas"] = nodoVigas;

    std::string rutaCompleta = "../mapas/"+ nombre_mapa + extension;  
    std::ofstream archivoSalida(rutaCompleta);
    archivoSalida << nodoPrincipal;

    std::cout << "Se ha creado el nuevo archivo YAML." << std::endl;
}




void Game::renderizar()
{
 
    view.renderizar_fondo_pantalla(fondo_eleguido);
    SDL_Color color = {255, 255, 255, 255};
    view.renderizar_texto(this->objeto_renderizar, 20, 20, color);
    for (Objeto objeto : objetos_creados)
    { // para mostrar las vigas
        view.renderizar_objeto(objeto);
    }

}

