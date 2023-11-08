#ifndef VIGADTO_H_
#define VIGADTO_H_
#include <ostream>
#include <iostream>

class VigaDTO
{
public:
    bool tipo; // true es la larga false corta de 30
    int x;
    int y;
    int angulo;

    VigaDTO(bool tipo, int x, int y, int angulo) : tipo(tipo), x(x), y(y), angulo(angulo) {} // Declaración del constructor

    void mostrar() const { std::cout << "Viga tipo" << tipo << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

    
};

#endif // VIGADTO_H_
