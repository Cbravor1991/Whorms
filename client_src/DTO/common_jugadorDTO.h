#ifndef JUGADORDTO_H_
#define JUGADORDTO_H_

#include <string>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>

class JugadorDTO
{
public:
    int id;
    int x;
    int y;
    int angulo;
    bool is_running = true; // whether the character is currently running
	int run_phase = 0;      // run animation phase
    bool direccion = true;


    JugadorDTO(int id, int x, int y, int angulo) : id(id), x(x), y(y), angulo(angulo)
    {
    }

    void mostrar() const { std::cout << "Jugador id " << id << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

    int obtenerId() { return id; }

    void actualizar(JugadorDTO jugador) {
        run_phase = (run_phase + 1)%13;
        if(this->id != jugador.id) 
            return;//lanzar exepcion
        
        this->x = jugador.x;
        this->y = jugador.y;
        this->angulo = jugador.angulo;
    }
};

#endif
