#ifndef JUGADORDTO_H_
#define JUGADORDTO_H_

#include <string>
#include <map>
#include <vector>

class JugadorDTO
{
private:
int x;
int y;
int id;
int id_jugador_turno_actual;
bool turno_activo;

public:
JugadorDTO();
void cargar_posicion_x(const int& posicion_x);
void cargar_posicion_y(const int& posicion_y);
void cargar_id(const int& id_jugador);
void cargar_id_turno_jugador(const int& id_jugador);
void cargar_turno(bool turno);


int obtener_posicion_x();
int obtener_posicion_y();
int obtener_id();
int obtener_id_turno_jugador();
bool obtener_turno();

   
};

#endif 
