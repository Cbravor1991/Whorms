#include "common_jugadorDTO.h"

void JugadorDTO::cargar_armas(int arma) {
    this->arma = arma;
     std::cout << "Soy jugador " << id << " con arma: " << arma << std::endl;
}

JugadorDTO::JugadorDTO(int id, int x, int y, bool direccion, int angulo) : id(id), x(x), y(y), direccion(direccion), angulo(angulo), vida(100)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    color = {static_cast<uint8_t>(0 + rand() % (255 - 0 + 1)),
            static_cast<uint8_t>(0 + rand() % (255 - 0 + 1)),
            static_cast<uint8_t>(0 + rand() % (255 - 0 + 1)),
            static_cast<uint8_t>(0 + rand() % (255 - 0 + 1))};
}

void JugadorDTO::mostrar() const { std::cout << "Jugador id " << id << " en X: " << x << " Y: " << y << " Angulo:misil:" << angulo << std::endl; }

int JugadorDTO::obtenerId() { return id; }

void JugadorDTO::activa_animacion(bool permiso)
{
    is_running = permiso;
}

void JugadorDTO::actualizar(JugadorDTO jugador)
{

    status.update_animation();
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
    status.render(renderer, tex_manager, x, y, direccion, angulo);

}

int JugadorDTO::posicion_x() {
    return x;
}

int JugadorDTO::posicion_y() {
    return y;
}

int JugadorDTO::obtener_vida() {
    return vida;
}

SDL_Color JugadorDTO::obtener_color() {
    return color;
}
