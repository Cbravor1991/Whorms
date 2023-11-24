#include "common_armaDTO.h"

ArmaDTO::ArmaDTO(int id, int id_cliente, int arma, int ammo) : id(id), id_cliente(id_cliente), arma(arma), ammo(ammo)
{
    type = TIPO_ARMA;
}

void ArmaDTO::cambiar_render(bool &permiso)
{
}

void ArmaDTO::cargar(std::map<int, JugadorDTO> &jugadores)
{
    int id_gusano = id * 10 + id_cliente;
    auto it = jugadores.find(id_gusano);

    if (it != jugadores.end())
    {
        // Si el jugador existe, carga el arma al jugador
        it->second.cargar_armas(arma, ammo);
    }
    else
    {
        // Si el jugador no existe, puedes manejar esta situación según tus necesidades
        // Aquí, simplemente no se hace nada, pero puedes agregar la lógica que necesites.
    }
}
