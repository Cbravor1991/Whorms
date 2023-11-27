// Turno.h
#ifndef TURNO_H
#define TURNO_H

#include <vector>
#include <cstddef>

const int VACIO = 0;

class Turno
{
public:
    Turno();
    int cambiar_turno();
    void eliminar_id(int id);
    void agregar_id(int id);
    int recibir_turno();
    std::vector<int> obtener_jugadores();

private:
    std::vector<int> jugadores;
    size_t turno_actual;
};

#endif