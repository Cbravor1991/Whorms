// Objeto.h
#ifndef OBJETO_H
#define OBJETO_H

class Objeto
{
public:
    Objeto() {}
    // virtual void interactuar() = 0;
    bool getDireccion() const { return direccion; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setCoordenadas(int new_x, int new_y)
    {
        x = new_x;
        y = new_y;
    }
    void setDireccion(bool new_direccion) { direccion = new_direccion; }

protected:
    int x;
    int y;
    bool direccion;
};

#endif // OBJETO_H