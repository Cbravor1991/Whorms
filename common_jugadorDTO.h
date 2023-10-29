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

public:
JugadorDTO();
void cargar_posicion_x(const int& posicion_x);
void cargar_posicion_y(const int& posicion_y);
void cargar_id(const int& id_jugador);


int obtener_posicion_x();
int obtener_posicion_y();
int obtener_posicion_id();
  

   
};

#endif 
