// Turno.h
#ifndef TURNO_H
#define TURNO_H

#include <vector>

class Turno
{
public:
    Turno();
    int cambiar_turno();
    void eliminar_id(int id);
    void agregar_id(int id);

private:
    std::vector<int> jugadores;
    size_t turno_actual;
};

#endif