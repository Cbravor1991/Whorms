#ifndef JUGADORDTO_H_
#define JUGADORDTO_H_

#include <string>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <SDL2pp/SDL2pp.hh>

class JugadorDTO
{
private:
    int id;
    int x;
    int y;
    bool direccion;
    int angulo;
    bool is_running;   // whether the character is currently running
    int run_phase = 0; // run animation phase
public:
    JugadorDTO(int id, int x, int y, bool direccion, int angulo);

    void mostrar() const;

    int obtenerId();

    void activa_animacion(bool permiso);

    void actualizar(JugadorDTO jugador);

    void renderizar(SDL2pp::Renderer &renderer);

    int posicion_x();

    int posicion_y();
};

#endif
