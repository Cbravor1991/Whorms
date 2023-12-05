#include "game.h"

#include <SDL2pp/SDL2pp.hh>

#define SLEEP_RATE (4.0f / 35.0f) * 50

void Game::subir_mapa(std::string path_mapa_editar, int &id_fondo) {
    ConfiguracionMapa configuracion_mapa = ConfiguracionMapa::obtener_configuracion_mapa("../../mapas/" + path_mapa_editar + ".yaml");
    std::vector<PosicionSpawn> spawns = configuracion_mapa.getSpawns();
    if (!spawns.empty()) {
        spawns_automaticos = false;
        for (PosicionSpawn spawn : spawns) { 
            Objeto nuevo_spawn(2, spawn.obtener_x(), spawn.obtener_y(), 0, contador_id_objetos);
            objetos_creados.push_back(nuevo_spawn);         
            contador_id_objetos++;          
        }
    }
    std::vector<PosicionViga> vigas = configuracion_mapa.getVigas();
    
    if (!vigas.empty()) {
        for (PosicionViga viga : vigas) { 
            Objeto viga_creada(viga.obtener_tipo(), viga.obtener_x(), viga.obtener_y(), viga.obtener_angulo(), contador_id_objetos);
            objetos_creados.push_back(viga_creada);
            contador_id_objetos++;
        }
    }
    id_fondo = configuracion_mapa.getFondo();

}

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
{   
    
       if (fondo_seleccionado == "noche") {
        this->id_mapa = FONDO_NOCHE;
    } else if (fondo_seleccionado == "snow") {
        this->id_mapa = FONDO_NIEVE;
    } else {
        this->id_mapa = FONDO_DIA;
    }
    nombre_mapa = nombre_mapa_recibido;
    fondo_elegido = fondo_seleccionado;
    view.reproducir_musica();

    while (true)
    {
       
        if (not this->gameLoop())
        {   
             break;
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
                if (contador_objetos <= cantidad_objetos) {
                    this->objeto_renderizar = tipos_objetos.at(contador_objetos);
                } else {
                    contador_objetos = -1;
                }
                break;
            }
            case (SDLK_t):
            {
                if (this->objeto_renderizar == "Borrar" && objetos_creados.size() != 0) {
                    contador_obj_seleccionados++;

                    if (contador_obj_seleccionados >= (int)objetos_creados.size()) {
                        contador_obj_seleccionados = 0;  
                    }

                id_objeto_seleccionado = objetos_creados.at(contador_obj_seleccionados).getId();
                }
                break;
            }
            case (SDLK_BACKSPACE):
            {
                if (this->objeto_renderizar == "Borrar" && this->id_objeto_seleccionado != -1) {
                    auto it = std::remove_if(objetos_creados.begin(), objetos_creados.end(),
                                             [this](const Objeto &obj)
                                             {
                                                 return obj.getId() == this->id_objeto_seleccionado;
                                             });

                    objetos_creados.erase(it, objetos_creados.end());
                }
                break;  
            } 
            case (SDLK_m):
            {
                  view.mutear_sonidos();
                
                break;
            }
            case (SDLK_RETURN):
            { // Enter
                guardar_datos();
                return false;
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
                    Objeto viga(0, mouseX, mouseY, 45, contador_id_objetos);
                    objetos_creados.push_back(viga);
                    contador_id_objetos++;
                } else if (this->objeto_renderizar == "Gusano") {
                    Objeto gusano(2, mouseX, mouseY, 0, contador_id_objetos);
                    objetos_creados.push_back(gusano);
                    std::cout << mouseX << std::endl;
                    std::cout << mouseY << std::endl;
                    contador_id_objetos++;
                    spawns_automaticos = false;
                } else if (this->objeto_renderizar == "Viga corta -45°") {
                    Objeto viga(0, mouseX, mouseY, -45, contador_id_objetos);
                    objetos_creados.push_back(viga);
                    contador_id_objetos++;
                } else if (this->objeto_renderizar == "Viga corta 0°") {
                    Objeto viga(0, mouseX, mouseY, 0, contador_id_objetos);
                    objetos_creados.push_back(viga);
                    contador_id_objetos++;
                } else if (this->objeto_renderizar == "Viga larga 45°") {
                    Objeto viga(1, mouseX, mouseY, 45, contador_id_objetos);
                    objetos_creados.push_back(viga);
                    contador_id_objetos++;
                } else if (this->objeto_renderizar == "Viga larga 0°") {
                    Objeto viga(1, mouseX, mouseY, 0, contador_id_objetos);
                    objetos_creados.push_back(viga);
                    contador_id_objetos++;
                } else if (this->objeto_renderizar == "Viga larga -45°") {
                    Objeto viga(1, mouseX, mouseY, -45, contador_id_objetos);
                    objetos_creados.push_back(viga);
                    contador_id_objetos++;
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
    nodoPrincipal["fondo"]["pantalla"] = this->id_mapa;

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

    std::string rutaCompleta = "../../mapas/"+ nombre_mapa + extension;  
    std::ofstream archivoSalida(rutaCompleta);
    archivoSalida << nodoPrincipal;

    std::cout << "Se ha creado el nuevo mapa." << std::endl;
}




void Game::renderizar()
{
    view.renderizar_fondo_pantalla(fondo_elegido);
    SDL_Color color = {255, 255, 255, 255};
    // usamos letras negras para nieve
    if (id_mapa == FONDO_NIEVE) {
        color = {0, 0, 0, 255};
    }
    view.renderizar_texto(this->objeto_renderizar, 20, 20, color);
    view.renderizar_texto("Apriete R para seleccionar objeto", 800, 550, color);
    view.renderizar_texto("Para borrar, seleccione el objeto con T y apriete DELETE", 800, 430, color);
    view.renderizar_texto("Para guardar y salir, apriete ENTER", 800, 450, color);
    if (this->objeto_renderizar != "Borrar") {
        id_objeto_seleccionado = -1;
    }
    for (Objeto objeto : objetos_creados)
    { 
        view.renderizar_objeto(objeto, id_objeto_seleccionado);
    }
}

