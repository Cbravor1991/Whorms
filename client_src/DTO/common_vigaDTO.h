#ifndef VIGADTO_H_
#define VIGADTO_H_
#include <ostream>
#include <iostream>

class VigaDTO
{
private:
    bool tipo;
    int x;
    int y;
    int angulo;

public:
    VigaDTO(bool tipo, int x, int y, int angulo) : tipo(tipo), x(x), y(y), angulo(angulo) {} // Declaración del constructor

    void mostrar() const { std::cout << "Viga tipo" << tipo << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }
};

#endif // VIGADTO_H_
