#include "common_jugadorDTO.h"


JugadorDTO::JugadorDTO(int id, int x, int y, bool direccion, int angulo, int vida, bool en_movimiento) : id(id), x(x), y(y), direccion(direccion), angulo(angulo), vida(vida), is_running(en_movimiento)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    color = {static_cast<uint8_t>(0 + rand() % (255 - 0 + 1)),
             static_cast<uint8_t>(0 + rand() % (255 - 0 + 1)),
             static_cast<uint8_t>(0 + rand() % (255 - 0 + 1)),
             static_cast<uint8_t>(0 + rand() % (255 - 0 + 1))};

    this->status.reset(new WormIdle());

    this->weapon.reset(new WormNoWeapon());
}

void JugadorDTO::mostrar() const { std::cout << "Jugador id " << id << " en X: " << x << " Y: " << y << " Angulo:" << angulo << "vida " << vida << "mov" << is_running << std::endl; }
int JugadorDTO::obtenerId() { return id; }

void JugadorDTO::activa_animacion(bool permiso)
{
    is_running = permiso;
}

void JugadorDTO::actualizar(JugadorDTO jugador)
{

    status->update_animation();
    if (this->id != jugador.id)
        return; // lanzar exepcion

    this->x = jugador.x;
    this->y = jugador.y;
    this->angulo = jugador.angulo;
    this->vida = jugador.vida;
    this->direccion = jugador.direccion;
    
    // if((this->x != jugador.x) and (this->y != jugador.y)) {
    //     this->is_running = true;
    // }

    if ((this->is_running) and (this->status->getState() != WALK)) {
        this->status.reset(new WormWalk());
    }else if ((!this->is_running) and (this->status->getState() != IDLE)){
        this->status.reset(new WormIdle());
    }

}

void JugadorDTO::renderizar(SDL2pp::Renderer &renderer, TextureManager &tex_manager)
{   
    int flip;
    if(this->direccion) flip = SDL_FLIP_HORIZONTAL;
    else flip = SDL_FLIP_NONE;

    if((this->status->getState() == IDLE) and (this->weapon->getWeapon() != NO_WEAPON)) {
        this->weapon->render(renderer, tex_manager, x, y, flip, angulo);

    } else {
        status->render(renderer, tex_manager, x, y, flip, angulo);
    }
}

int JugadorDTO::posicion_x()
{
    return x;
}

int JugadorDTO::posicion_y()
{
    return y;
}

int JugadorDTO::obtener_vida()
{
    return vida;
}

SDL_Color JugadorDTO::obtener_color()
{
    return color;
}

void JugadorDTO::cargar_armas(int arma)
{
    this->arma = arma;
    if(arma == AIR_STRIKE) this->weapon.reset(new WormAirstike());
    else if (arma == TELEPORT) this->weapon.reset(new WormTeleport());
    else this->weapon.reset(new WormNoWeapon());

    std::cout << "Soy jugador " << id << " con arma: " << arma << std::endl;
}

void JugadorDTO::stop_running() {

    if(!this->is_running) return;

    this->is_running = false;
    this->status.reset(new WormIdle());
}
