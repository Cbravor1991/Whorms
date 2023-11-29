#include "worm_bazooka.h"
#include "../../actions/shoot_power.h"

WormBazooka::WormBazooka(int ammo) : mira(LONG_SIGHT), municion(INFINITE_AMMO) {}

void WormBazooka::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/bazooka/wbazlnk.png";
    // ver de usar el sprite de apuntar
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 6;

    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del sprite queres que te cargue
        SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
        -angulo,                            // rotation
        SDL2pp::NullOpt,                    // rotation center - not needed
        flip                                // flip
    );

    potencia.render(renderer, tex_manager, x, y, angulo, mira.recibir_angulo(), flip);
    mira.render(renderer, tex_manager, x, y, angulo, flip);
}

Action *WormBazooka::usar(int x, int y, bool direccion)
{
    int angulo = mira.recibir_angulo();
    int pot = potencia.obtenerPotencia();
    Action *accion = new PowerShoot(angulo, direccion, pot);
    //Action *accion = new Shoot(angulo, direccion);
    potencia.resetearPotencia();
    return accion;
}

const int WormBazooka::getWeapon()
{

    return BAZOOKA;
}

void WormBazooka::increaseAngle()
{
    mira.aumentar_angulo();
}

void WormBazooka::decreaseAngle()
{
    mira.disminuir_angulo();
}

int WormBazooka::getAmmo()
{
    return municion;
}

void WormBazooka::setTimer(int segundos) {}

int WormBazooka::getTimer() 
{
    return 0;
}

void WormBazooka::increasePower() 
{
    //potencia++;
    potencia.aumentarPotencia();
}

bool WormBazooka::isMaxPower() 
{//como no tiene potencia, nunca llega a MAXIMA_POTENCIA
    return (potencia.obtenerPotencia() >= MAXIMA_POTENCIA);
}

