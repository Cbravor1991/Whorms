#include "common_jugadorDTO.h"

void JugadorDTO::setear_color()
{
    if (id == 1)
    {
        color = {255, 0, 0, 255}; // Rojo
    }
    else if (id == 2)
    {
        color = {255, 165, 0, 255}; // Naranja
    }
    else if (id == 3)
    {
        color = {255, 255, 0, 255}; // Amarillo
    }
    else if (id == 4)
    {
        color = {0, 255, 0, 255}; // Verde
    }
    else if (id == 5)
    {
        color = {0, 255, 255, 255}; // Celeste
    }
    else if (id == 6)
    {
        color = {0, 0, 255, 255}; // Azul
    }
    else if (id == 7)
    {
        color = {255, 0, 255, 255}; // Rosa
    }
}

JugadorDTO::JugadorDTO(int id, int x, int y, bool direccion, int angulo, int vida, bool en_movimiento, int id_cliente) : id(id), x(x), y(y), direccion(direccion), angulo(angulo), vida(vida), is_running(en_movimiento), id_cliente(id_cliente)
{
    setear_color();

    this->status.reset(new WormIdle());

    this->weapon.reset(new WormNoWeapon(0));
}

void JugadorDTO::mostrar() const { std::cout << "Jugador id " << id << " en X: " << x << " Y: " << y << " Angulo:" << angulo << "vida " << vida << "mov" << is_running << std::endl; }
int JugadorDTO::obtenerId()
{

    return id * 100 + id_cliente;
}

void JugadorDTO::activa_animacion(bool permiso)
{
    is_running = permiso;
}

void JugadorDTO::actualizar(JugadorDTO jugador)
{

    status->update_animation();
    if (this->obtenerId() != jugador.obtenerId())
        return;

    if ((this->x != jugador.x) or (this->y != jugador.y))
        this->is_running = true;

    this->x = jugador.x;
    this->y = jugador.y;
    this->angulo = jugador.angulo;
    this->vida = jugador.vida;
    this->direccion = jugador.direccion;

    if ((this->is_running) and (this->status->getState() != WALK))
    {
        this->status.reset(new WormWalk());
    }
    else if ((!this->is_running) and (this->status->getState() != IDLE))
    {
        this->status.reset(new WormIdle());
    }
}

void JugadorDTO::renderizar(SDL2pp::Renderer &renderer, TextureManager &tex_manager)
{
    int flip;
    if (this->direccion)
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;

    if ((this->status->getState() == IDLE) and (this->weapon->getWeapon() != NO_WEAPON))
    {
        this->weapon->render(renderer, tex_manager, x, y, flip, angulo);
    }
    else
    {
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

int JugadorDTO::obtener_vida() const
{
    return vida;
}

SDL_Color JugadorDTO::obtener_color() const
{
    return color;
}

void JugadorDTO::cargar_armas(int arma, int ammo)
{
    this->arma = arma;
    // actualmente, solo estan implementadas Airstrike y Teleport
    if (arma == AIR_STRIKE)
        this->weapon.reset(new WormAirstike(ammo));
    else if (arma == TELEPORT)
        this->weapon.reset(new WormTeleport(ammo));
    else if (arma == BAT)
        this->weapon.reset(new WormBat(ammo));
    else if (arma == DYNAMITE)
        this->weapon.reset(new WormDynamite(ammo));
    else if (arma == BAZOOKA)
        this->weapon.reset(new WormBazooka(ammo));
    else if (arma == MORTAR)
        this->weapon.reset(new WormMortar(ammo));
    else if (arma == GREEN_GRENADE)
        this->weapon.reset(new WormGreenGrenade(ammo));
    else if (arma == CLUSTER_GRENADE)
        this->weapon.reset(new WormClusterGrenade(ammo));
    else if (arma == HOLY_GRENADE)
        this->weapon.reset(new WormHolyGrenade(ammo));
    else if (arma == BANANA)
        this->weapon.reset(new WormBanana(ammo));
    else
        this->weapon.reset(new WormNoWeapon(ammo));

    // std::cout << "Soy jugador " << id << " con arma: " << arma << std::endl;
}

Action *JugadorDTO::usar_arma(int x, int y)
{
    return weapon->usar(x, y, direccion);
}

void JugadorDTO::stop_running()
{

    if (!this->is_running)
        return;

    frames_hasta_frenarse++;

    if(frames_hasta_frenarse >= CANTIDAD_FRAMES_FRENAR) {
        this->is_running = false;
        this->status.reset(new WormIdle());
        frames_hasta_frenarse = 0;
    }
    
}

void JugadorDTO::aumentar_angulo_arma()
{
    weapon->increaseAngle();
}

void JugadorDTO::disminuir_angulo_arma()
{
    weapon->decreaseAngle();
}

int JugadorDTO::obtenerMunicion() {
    return this->weapon->getAmmo();
}

void JugadorDTO::cambiar_timer_arma(int segundos) 
{
    this->weapon->setTimer(segundos);
}

void JugadorDTO::aumentar_potencia()
{
    this->weapon->increasePower();
}

int JugadorDTO::potencia_arma_es_maxima() 
{
    return this->weapon->isMaxPower();
}

int JugadorDTO::obtener_arma() 
{
    return this->weapon->getWeapon();
}

int JugadorDTO::obtenerIdCliente() const
{
    return this->id;
}
