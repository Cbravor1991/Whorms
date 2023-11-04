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

public:
    VigaDTO(bool tipo, int x, int y) : tipo(tipo), x(x), y(y) {} // Declaración del constructor

    void mostrar() const { std::cout << "Viga tipo" << tipo << " en X: " << x << " Y: " << y << std::endl; }
};

#endif // VIGADTO_H_
