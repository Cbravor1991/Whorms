#include "common_objetoDTO.h"

ObjetoDTO::ObjetoDTO(int tipo, int x, int y, bool direccion, int angulo, bool explosion) : x(x), y(y), direccion(direccion), angulo(angulo), tipo(tipo), explosion(explosion)
{
}

void ObjetoDTO::mostrar() const { std::cout << "en X: " << x << " Y: " << y << std::endl; }

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

    this->tipo = jugador.tipo;
    this->x = jugador.x;
    this->y = jugador.y;
    this->angulo = jugador.angulo;
    this->direccion = jugador.direccion;
    this->is_running = jugador.is_running;
}

void ObjetoDTO::renderizar(SDL2pp::Renderer &renderer, TextureManager &tex_manager)
{
    // mostrar();

    std::string path = this->obtener_path();
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
        SDL_FLIP_VERTICAL                                // vertical flip

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

bool ObjetoDTO::exploto()
{

    return explosion;
}

std::string ObjetoDTO::obtener_path()
{

    std::string path;
    switch (this->tipo)
    {
    case (AIR_STRIKE):
    {
        path = "/sprites/Weapon/In-game/airmisil.png";
        break;
    }
    case (DYNAMITE):
    {
        path = "/sprites/Weapon/In-game/dynamite.png";
        break;
    }
    case (BAZOOKA):
    {
        path = "/sprites/Weapon/In-game/bzkmisil.png";
        break;
    }
    case (MORTAR):
    {
        path = "/sprites/Weapon/In-game/mortar.png";
        break;
    }
    case (GREEN_GRENADE):
    {
        path = "/sprites/Weapon/In-game/grenade.png";
        break;
    }
    case (CLUSTER_GRENADE):
    {
        path = "/sprites/Weapon/In-game/cgrenade.png";
        break;
    }
    case (HOLY_GRENADE):
    {
        path = "/sprites/Weapon/In-game/hgrenade.png";
        break;
    }
    case (BANANA):
    {
        path = "/sprites/Weapon/In-game/banana.png";
        break;
    }
    case (PROVISION):
    {
        path = "/sprites/misc/crates/wcrate0.png";
        break;
    }
    default:
        std::cout << "Si llega aca es porque es un proyectil no valido o un proyectil no implementado\n";
        break;
    }
    return path;
}
