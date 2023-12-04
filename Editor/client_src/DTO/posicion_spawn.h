#ifndef POSICION_SPAWN_H
#define POSICION_SPAWN_H

class PosicionSpawn
{
private:
    int x;
    int y;

public:
    PosicionSpawn(int x, int y) : x(x), y(y) {}

    int obtener_x() const {
        return x;
    }

    int obtener_y() const {
        return y;
    }
};

#endif