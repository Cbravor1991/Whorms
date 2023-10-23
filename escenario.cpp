#include "escenario.h"

Escenario::Escenario(std::uint16_t x_size, std::uint16_t y_size, MonitorJugadores *monitor) : x_size(x_size),
                                                                                              y_size(y_size), monitor(monitor),
                                                                                              map(y_size, std::vector<Objeto *>(x_size, nullptr))
{
}

void Escenario::avisar_desconexion(int jugador)
{
    monitor->avisar_desconexion();
    std::map<int, Gusano *> &gusanosJugador = gusanos[jugador];
    // Liberar la memoria de los gusanos del jugador
    for (auto &pair : gusanosJugador)
    {
        delete pair.second;
    }
    // Borrar el mapa de gusanos del jugador
    gusanos.erase(jugador);
    // actualizar_jugadores()
    cantidad_jugadores--;
}

int Escenario::agregar_gusano()
{
    int jugador = cantidad_jugadores;
    // Crear un nuevo gusano
    Gusano *nuevoGusano = new Gusano();
    std::map<int, Gusano *> nuevoGusanos;
    nuevoGusanos[1] = nuevoGusano;
    gusanos[jugador] = nuevoGusanos;
    cantidad_jugadores++;
    std::pair<int, int> spawn = spawns.front();
    spawns.erase(spawns.begin());
    // Asignar las coordenadas del gusano
    nuevoGusano->setCoordenadas(spawn.first, spawn.second);
    map[spawn.second][spawn.first] = nuevoGusano;
    return jugador;
}

void Escenario::colocar_viga(int x, int y, bool tipo, int inclinacion)
{
    if (tipo == 0)
    {
        for (int i = x; i < x + 30; i++)
        {
            for (int j = y; j < y + 8; j++)
            {
                if (i < x_size)
                {
                    map[y][i] = new Bloque(); // Crea un nuevo objeto Bloque y asigna el puntero en la matriz
                    if ((i - x) % 10 == 5 and j == y)
                    {
                        spawns.push_back(std::make_pair(i, y - 1));
                    }
                }
            }
        }
    }
    else
    {
        for (int i = x; i < x + 60; i++)
        {
            for (int j = y; j < y + 8; j++)
            {
                if (i < x_size)
                {
                    map[y][i] = new Bloque(); // Crea un nuevo objeto Bloque y asigna el puntero en la matriz
                    if ((i - x) % 10 == 5 and j == y)
                    {
                        spawns.push_back(std::make_pair(i, y - 1));
                    }
                }
            }
        }
    }
    monitor->agregar_viga(tipo, x, y);
}

void Escenario::mover_gusano_derecha(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusanoAMover = gusanosDelJugador[gusano];
    mover_derecha(gusanoAMover, 2);
    gravedad(gusanoAMover);
    int x = gusanoAMover->getX();
    int y = gusanoAMover->getY();
    monitor->actualizar_jugadores_jugador(jugador, x, y);
}

void Escenario::mover_gusano_izquierda(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusanoAMover = gusanosDelJugador[gusano];
    mover_izquierda(gusanoAMover, 2);
    gravedad(gusanoAMover);
    int x = gusanoAMover->getX();
    int y = gusanoAMover->getY();
    monitor->actualizar_jugadores_jugador(jugador, x, y);
}

void Escenario::mover_gusano_arriba_adelante(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusanoAMover = gusanosDelJugador[gusano];
    bool direccion = gusanoAMover->getDireccion();
    if (mover_arriba(gusanoAMover, 5))
    {
        if (direccion)
        {
            mover_derecha(gusanoAMover, 10);
        }
        else
        {
            mover_izquierda(gusanoAMover, 10);
        }
    }
    gravedad(gusanoAMover);
    int x = gusanoAMover->getX();
    int y = gusanoAMover->getY();
    monitor->actualizar_jugadores_jugador(jugador, x, y);
}

void Escenario::mover_gusano_arriba_atras(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusanoAMover = gusanosDelJugador[gusano];
    bool direccion = gusanoAMover->getDireccion();
    if (mover_arriba(gusanoAMover, 12))
    {
        if (direccion)
        {
            mover_izquierda(gusanoAMover, 2);
        }
        else
        {
            mover_derecha(gusanoAMover, 2);
        }
    }
    gravedad(gusanoAMover);
    int x = gusanoAMover->getX();
    int y = gusanoAMover->getY();
    monitor->actualizar_jugadores_jugador(jugador, x, y);
}

void Escenario::mover(int x, int y, int nuevo_x, int nuevo_y)
{
    map[nuevo_y][nuevo_x] = map[y][x]; // Mover a la siguiente casilla
    map[y][x] = nullptr;               // Borrar la casilla actual
    map[nuevo_y][nuevo_x]->setCoordenadas(nuevo_x, nuevo_y);
    // actualizar_jugadores()
}

bool Escenario::mover_derecha(Objeto *objeto, int veces)
{
    int x = objeto->getX();
    int y = objeto->getY();
    objeto->setDireccion(true);
    for (int i = 0; i < veces; i++)
    {
        if (x + 1 < x_size)
        {
            if (map[y][x + 1] == nullptr)
            {
                mover(x, y, x + 1, y);
                x = x + 1;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Escenario::mover_izquierda(Objeto *objeto, int veces)
{
    int x = objeto->getX();
    int y = objeto->getY();
    objeto->setDireccion(false);
    for (int i = 0; i < veces; i++)
    {
        if (x - 1 >= 0)
        {
            if (map[y][x - 1] == nullptr)
            {
                mover(x, y, x - 1, y);
                x = x - 1;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Escenario::mover_arriba(Objeto *objeto, int veces)
{
    int x = objeto->getX();
    int y = objeto->getY();
    for (int i = 0; i < veces; i++)
    {
        if (y - 1 >= 0)
        {
            if (map[y - 1][x] == nullptr)
            {
                mover(x, y, x, y - 1);
                y = y - 1;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Escenario::gravedad(Objeto *objeto)
{
    int x = objeto->getX();
    int y = objeto->getY();
    if (y + 1 < y_size)
    {
        if (map[y + 1][x] == nullptr)
        {
            mover(x, y, x, y + 1);
            gravedad(objeto);
        }
    }
}

Escenario::~Escenario()
{
    // Liberar la memoria de los gusanos
    for (auto &jugadorGusanos : gusanos)
    {
        for (auto &gusanoPair : jugadorGusanos.second)
        {
            delete gusanoPair.second;
        }
    }

    // Limpiar el vector de spawns
    spawns.clear();

    // Liberar la memoria de los objetos en el mapa
    for (std::vector<Objeto *> &fila : map)
    {
        for (Objeto *objeto : fila)
        {
            delete objeto;
        }
    }
}
