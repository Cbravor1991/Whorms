#include "common_objetoDTO.h"

ObjetoDTO::ObjetoDTO(int tipo, int x, int y, bool direccion, int angulo, bool explosion) : x(x), y(y), direccion(direccion), angulo(angulo), tipo(tipo), explosion(explosion)
{

}

void ObjetoDTO::mostrar() const { std::cout << "en X: " << x << " Y: " << y <<  std::endl; }

int ObjetoDTO::obtenerId() { return id; }

void ObjetoDTO::activa_animacion(bool permiso)
{
    is_running = permiso;
}

void ObjetoDTO::actualizar(ObjetoDTO jugador)
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

void ObjetoDTO::renderizar(SDL2pp::Renderer &renderer, TextureManager &tex_manager)
{
    mostrar();

   
    std::string path = "/sprites/Weapon/Icons/airmisil.png";
    std::shared_ptr<SDL2pp::Texture> sprites = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0; // by default, standing sprite
    if (is_running)
    {
        src_y = 60 * 1;
    }
    renderer.Copy(
        *sprites,
        SDL2pp::Rect(src_x, src_y, 60, 60),              // que parte del spike queres que te cargue
        SDL2pp::Rect(this->x, 200 - this->y, 50, 50), 0, // la posicion en pantalla y el tamaño
        SDL2pp::NullOpt,                                 // rotation center - not needed
        SDL_FLIP_VERTICAL                              // vertical flip

    );
}

int ObjetoDTO::posicion_x()
{
    return x;
}

int ObjetoDTO::posicion_y()
{
    return y;
}