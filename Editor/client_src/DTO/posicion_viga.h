#ifndef POSICION_VIGA_H
#define POSICION_VIGA_H

class PosicionViga
{
private:
    bool tipo;
    int x;
    int y;
    int angulo;

public:
    PosicionViga(bool tipo, int x, int y, int angulo) : tipo(tipo), x(x), y(y), angulo(angulo) {}

    int obtener_x() const {
        return x;
    }

    int obtener_y() const {
        return y;
    }

    bool obtener_tipo() const {
        return tipo;
    }

    int obtener_angulo() const {
        return angulo;
    }
};

#endif