#include "common_jugadorDTO.h"

JugadorDTO::JugadorDTO(int id, int x, int y, bool direccion, int angulo) : id(id), x(x), y(y), direccion(direccion), angulo(angulo)
{
}

void JugadorDTO::mostrar() const { std::cout << "Jugador id " << id << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

int JugadorDTO::obtenerId() { return id; }

void JugadorDTO::activa_animacion(bool permiso)
{
    is_running = permiso;
}

void JugadorDTO::actualizar(JugadorDTO jugador)
{
    run_phase = (run_phase + 1) % 13;
    if (this->id != jugador.id)
        return; // lanzar exepcion

    this->x = jugador.x;
    this->y = jugador.y;
    this->angulo = jugador.angulo;
    this->direccion = jugador.direccion;
    this->is_running = jugador.is_running;
}

void JugadorDTO::renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager)
{
    std::string path = "/sprites/worm/walk/wwalk.png";
    std::shared_ptr<SDL2pp::Texture> sprites = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0; // by default, standing sprite
    if (is_running)
    {

        src_y = 60 * run_phase;
    }
    if (direccion)
    {
        renderer.Copy(
            *sprites,
            SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del spike queres que te cargue
            SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
            0.0,                                // don't rotate
            SDL2pp::NullOpt,                    // rotation center - not needed
            SDL_FLIP_HORIZONTAL                 // vertical flip
        );
    }
    else
    {

        renderer.Copy(
            *sprites,
            SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del spike queres que te cargue
            SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
            0.0,                                // don't rotate
            SDL2pp::NullOpt,                    // rotation center - not needed
            SDL_FLIP_NONE                       // vertical flip
        );
    }
}

int JugadorDTO::posicion_x() {
    return x;
}

int JugadorDTO::posicion_y() {
    return y;
}