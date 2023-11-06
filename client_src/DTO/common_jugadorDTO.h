#ifndef JUGADORDTO_H_
#define JUGADORDTO_H_

#include <string>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>

class JugadorDTO
{
private:
    int id;
    int x;
    int y;
    int angulo;

public:
    JugadorDTO(int id, int x, int y, int angulo) : id(id), x(x), y(y), angulo(angulo)
    {
    }

    void mostrar() const { std::cout << "Jugador id " << id << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

    int obtenerId() { return id; }

    void actualizar(JugadorDTO jugador) {
        if(this->id != jugador.id) 
            return;//lanzar exepcion
        
        this->x = jugador.x;
        this->y = jugador.y;
        this->angulo = jugador.angulo;
    }
};

#endif
