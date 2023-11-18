#include "common_armaDTO.h"

ArmaDTO::ArmaDTO(int id, int arma) : id(id), arma(arma)
{
}

void ArmaDTO::cambiar_render(bool &permiso)
{
 
}

void ArmaDTO::cargar(std::map<int, JugadorDTO>& jugadores){
  auto it = jugadores.find(id);
    
    if (it != jugadores.end()) {
        // Si el jugador existe, carga el arma al jugador
        it->second.cargar_armas(arma);
    } else {
        // Si el jugador no existe, puedes manejar esta situación según tus necesidades
        // Aquí, simplemente no se hace nada, pero puedes agregar la lógica que necesites.
    }
}


