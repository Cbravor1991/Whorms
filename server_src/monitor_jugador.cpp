#include "monitor_jugador.h"
#include "data/viento_velocidad.h"

int MonitorJugadores::cambiar_turno()
{
    int id_turno = turno.cambiar_turno();
    return id_turno;
}

std::vector<int> MonitorJugadores::obtener_jugadores()
{
    return turno.obtener_jugadores();
}

void MonitorJugadores::enviar_ganador()
{
    int id_ganador = recibir_turno();
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new Ganador(id_ganador));
    }
}

void MonitorJugadores::comenzar_juego(Queue<Accion *> *cola, int tipo_fondo)
{
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->jugar(cola, tipo_fondo);
    }
}

void MonitorJugadores::mandar_viento(VientoVelocidad viento)
{
    Data *data;
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        data = new VientoVelocidad(viento);
        jugador->recibir_comando(data);
    }
}

void MonitorJugadores::enviar_turno(int id_gusano)
{
    int id_turno = turno.recibir_turno();
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new CambioTurno(id_turno, id_gusano));
    }
}

int MonitorJugadores::recibir_turno()
{
    int id_turno = turno.recibir_turno();
    return id_turno;
}

void MonitorJugadores::mandar_paquete_gusanos(std::vector<PosicionJugador> jugadores)
{
    for (const auto &entry : this->jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new PaqueteGusanos(jugadores));
    }
}

void MonitorJugadores::mandar_paquete_objetos(std::vector<PosicionLanzable> objetos)
{
    for (const auto &entry : this->jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new PaqueteObjetos(objetos));
    }
}

void MonitorJugadores::mandar_arma(int jugador_id, int gusano_id, int arma, int ammo)
{
    for (const auto &entry : this->jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new EquipacionArma(jugador_id, gusano_id, arma, ammo));
    }
}

void MonitorJugadores::mandar_segundos(int segundos)
{
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new Segundo(segundos));
    }
}

void MonitorJugadores::mandar_escenario(int x, int y, std::vector<PosicionViga> vigas, int id)
{
    Jugador *jugador = jugadores[id];
    jugador->recibir_comando(new EscenarioInformacion(x, y, vigas));
}

void MonitorJugadores::actualizar_jugadores_cantidad(int cantidad)
{
    std::cout << "Jugadores " << cantidad
              << ", esperando al resto de tus amigos…" << std::endl;
}

void MonitorJugadores::agregar_jugador(Jugador *jugador)
{
    actualizar_cantidad_jugadores(1);

    int id = cantidad_jugadores;
    while (jugadores[id] != nullptr)
    {
        id++;
    }
    jugadores[id] = jugador;
    turno.agregar_id(id);
    jugador->asignar_id(id);
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

void MonitorJugadores::eliminar_turno(int id)
{
    turno.eliminar_id(id);
}

void MonitorJugadores::eliminar_jugadores_desconectados()
{
    // Utiliza un iterador para recorrer el mapa de jugadores
    auto it = jugadores.begin();
    while (it != jugadores.end())
    {
        int id = it->first;
        Jugador *jugador = it->second;

        if (!jugador->sigo_conectado())
        {
            jugadores_desconectados.push_back(jugador);
            it = jugadores.erase(it);
            turno.eliminar_id(id); // Elimina el ID del jugador de la clase Turno
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
    actualizar_jugadores_cantidad(cantidad_jugadores);
}

MonitorJugadores::~MonitorJugadores()
{
    limpiar_desconectados();
    // Liberar la memoria de todos los jugadores en el vector
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        delete jugador;
    }

    // Limpiar el vector
    jugadores.clear();
}
