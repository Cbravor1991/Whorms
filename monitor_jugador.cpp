#include "monitor_jugador.h"

void MonitorJugadores::agregar_mensaje(const std::string &mensaje)
{
    Mensaje ultimo_mensaje;
    ultimo_mensaje.cadena = mensaje;
    ultimo_mensaje.tipo_mensaje = true;
    actualizar_colas(ultimo_mensaje);
}

void MonitorJugadores::actualizar_colas(const Mensaje &mensaje)
{
    print_mensaje(mensaje);
    actualizar_jugadores(mensaje);
}

void MonitorJugadores::print_mensaje(Mensaje mensaje)
{
    std::unique_lock<std::mutex> lck(mutex_);
    if (mensaje.tipo_mensaje)
    {
        std::cout << mensaje.cadena << std::endl;
    }
    else if (mensaje.cadena != "")
    {
        std::cout << "Jugadores " << mensaje.cadena
                  << ", esperando al resto de tus amigos";
        std::cout << "."
                  << "."
                  << "." << std::endl;
    }
}

void MonitorJugadores::actualizar_jugadores(Mensaje mensaje)
{
    std::unique_lock<std::mutex> lck(mutex_);
    for (auto &jugador : jugadores)
    {
        jugador->recibir_mensaje(mensaje);
    }
}

void MonitorJugadores::agregar_jugador(Jugador *jugador)
{
    std::unique_lock<std::mutex> lck(mutex_);
    jugadores.push_back(jugador);
    lck.unlock();
    actualizar_cantidad_jugadores(1);
}

void MonitorJugadores::avisar_desconexion()
{
    eliminar_jugadores_desconectados();
    actualizar_cantidad_jugadores(-1);
}

void MonitorJugadores::limpiar_desconectados()
{
    // Liberar la memoria de todos los jugadores desconectados en el vector
    for (auto jugador : jugadores_desconectados)
    {
        delete jugador;
    }

    // Limpiar el vector
    jugadores_desconectados.clear();
}

void MonitorJugadores::eliminar_jugadores_desconectados()
{
    std::unique_lock<std::mutex> lck(mutex_);
    // Utiliza un iterador para recorrer la lista de jugadores
    auto it = jugadores.begin();
    while (it != jugadores.end())
    {
        Jugador *jugador = *it;
        if (!jugador->sigo_conectado())
        {
            jugadores_desconectados.push_back(jugador);
            it = jugadores.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void MonitorJugadores::actualizar_cantidad_jugadores(int cantidad)
{
    cantidad_jugadores += cantidad;
    Mensaje ultimo_mensaje;
    ultimo_mensaje.cadena = std::to_string(cantidad_jugadores);
    ultimo_mensaje.tipo_mensaje = false;
    actualizar_colas(ultimo_mensaje);
}

MonitorJugadores::~MonitorJugadores()
{
    limpiar_desconectados();
    // Liberar la memoria de todos los jugadores en el vector
    for (auto jugador : jugadores)
    {
        delete jugador;
    }

    // Limpiar el vector
    jugadores.clear();
}
