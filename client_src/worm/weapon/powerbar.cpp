#include "powerbar.h"
#include <cmath>
#include <set>

PowerBar::PowerBar() : potencia(0), renderizar(true) {}


    //agrego el angulo de la mira?
void PowerBar::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int worm_x, int worm_y, int worm_angle, int sight_angle, int flip) 
{   

    std::string path = "/Effects/potencia/blob.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0, crsh_x = 0, crsh_y = 0, offset = 5;
    //tengo que usar lo del angulo, pero ir aumentando el radio
    float angle_radians = 0;
    //agregar un offset para cuando tiene flip
    if (flip == SDL_FLIP_NONE)
    {
        angle_radians = (180 + sight_angle - worm_angle) * (M_PI / 180);
    }
    else
    {
        angle_radians = -(sight_angle + worm_angle) * (M_PI / 180);
    }

    //voy guardando en set cuales son las que se hicieron ya y si est, no la renderizo
    std::set<int> set;
    if (potencia && renderizar) {
        for(int i = 1; i <= MAXIMA_POTENCIA; i++) {
            if(i > potencia) {
                break;
            }
            int segmento = (int) ((i-1)/3); //3 es porque uso 4 frames distintos para la barra de potencia
            if(set.count(segmento)) {
                //si esta en el set, no renderizo
                continue;
            } 
            set.insert(segmento);
            //renderizo todo
            src_y = 64 * (6 + (2 * segmento));
            int radio = 18 + (4 * segmento);

            crsh_x = worm_x + (int)( radio * cos(angle_radians)) + offset;
            crsh_y = (int)((18 + (4 * segmento)) * sin(angle_radians)) - worm_y + offset;

            renderer.Copy(
                *texture,
                SDL2pp::Rect(src_x, src_y, 64, 64),         // que parte del sprite queres que te cargue
                SDL2pp::Rect(crsh_x, 200 + crsh_y, 40, 40), // la posicion en pantalla y el tamaño
                0,                                          // rotation
                SDL2pp::NullOpt,                            // rotation center - not needed
                SDL_FLIP_NONE                               // flip
            );
        }
    }
    //reseteo la potencia si es maxima luego de renderizar
    // if(potencia >= MAXIMA_POTENCIA) {
    //     potencia = 0;
    //     renderizar = false;
    // }
}


void PowerBar::aumentarPotencia() 
{   
    if(potencia >= MAXIMA_POTENCIA) {
        return;
    }
    potencia++;
}

int PowerBar::obtenerPotencia() {
    return potencia;
}

void PowerBar::resetearPotencia() 
{
    potencia = 0;
    renderizar = false;
}