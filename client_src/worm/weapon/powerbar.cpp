#include "powerbar.h"
#include <cmath>
#include <set>

PowerBar::PowerBar() : potencia(0), renderizar(true) {}

void PowerBar::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int worm_x, int worm_y, int worm_angle, int sight_angle, int flip) 
{   

    std::string path = "/Effects/potencia/blob.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0, crsh_x = 0, crsh_y = 0, offset = 5;
    float angle_radians = 0;
    if (flip == SDL_FLIP_NONE)
    {
        angle_radians = (180 + sight_angle - worm_angle) * (M_PI / 180);
    }
    else
    {
        angle_radians = -(sight_angle + worm_angle) * (M_PI / 180);
    }

    std::set<int> set;
    if (potencia && renderizar) {
        for(int i = 1; i <= MAXIMA_POTENCIA; i++) {
            if(i > potencia) {
                break;
            }
            int segmento = (int) ((i-1)/3);
            if(set.count(segmento)) {
                continue;
            } 
            set.insert(segmento);
            src_y = 64 * (6 + (2 * segmento));
            int radio = 18 + (4 * segmento);

            crsh_x = worm_x + (int)( radio * cos(angle_radians)) + offset;
            crsh_y = (int)((18 + (4 * segmento)) * sin(angle_radians)) - worm_y + offset;

            renderer.Copy(
                *texture,
                SDL2pp::Rect(src_x, src_y, 64, 64),        
                SDL2pp::Rect(crsh_x, 200 + crsh_y, 40, 40), 
                0,                                          
                SDL2pp::NullOpt,                            
                SDL_FLIP_NONE                               
            );
        }
    }
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