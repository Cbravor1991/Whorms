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

public:
    JugadorDTO(int id, int x, int y) : id(id), x(x), y(y) {}

    void mostrar() const { std::cout << "Jugador id " << id << " en X: " << x << " Y: " << y << std::endl; }
};

#endif
