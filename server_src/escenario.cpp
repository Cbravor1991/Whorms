#include "escenario.h"
#include <sstream>
#include "monitor_jugador.h"
#include "data/posicion_objeto.h"

Escenario::Escenario(std::uint16_t x_size, std::uint16_t y_size, MonitorJugadores *monitor) : x_size(x_size),
                                                                                              y_size(y_size), monitor(monitor)
{
    b2Vec2 gravity(0.0f, -10.0f);
    mundo = new Mundo(gravity);
    objetos = new std::vector<Objeto *>;
}

bool Escenario::en_movimiento()
{
    for (const auto &fila : gusanos)
    {
        for (const auto &par : fila.second)
        {
            Gusano *gusano = par.second;
            if (gusano->consultar_movimiento())
            {
                return true; // Si al menos un gusano está en movimiento, retorna true.
            }
        }
    }
    for (auto &objeto : *objetos)
    {
        if (objeto->consultar_movimiento())
        {
            return true;
        }
    }
    return false;
}

void Escenario::mandar_paquete()
{
    std::vector<PosicionJugador> posicion_jugadores;
    int muerto = 0;
    for (auto &entry : gusanos)
    {
        std::map<int, Gusano *> &gusanosPorJugador = entry.second;

        for (auto it = gusanosPorJugador.begin(); it != gusanosPorJugador.end(); /* no ++it here */)
        {

            Gusano *gusano = it->second;

            // Pedir la posición
            PosicionJugador posicion = gusano->conseguir_posicion_gusano();
            posicion_jugadores.push_back(posicion);
            if (!gusano->esta_vivo())
            {
                // Eliminar gusano si no está vivo
                mundo->eliminar_objeto(gusano);
                delete gusano;
                it = gusanosPorJugador.erase(it);
                muerto = entry.first;
            }
            else
            {
                ++it;
            }
        }
    }
    monitor->mandar_paquete_gusanos(posicion_jugadores);
    std::vector<PosicionLanzable> posicion_objetos;
    for (auto it = objetos->begin(); it != objetos->end();)
    {
        PosicionLanzable objeto = (*it)->conseguir_posicion();
        posicion_objetos.push_back(objeto);
        if (!(*it)->esta_vivo())
        {
            // Si el objeto no está vivo, elimínalo del vector.
            mundo->eliminar_objeto(*it);
            it = objetos->erase(it);
        }
        else
        {
            ++it; // Solo incrementa el iterador si no eliminaste el objeto.
        }
    }
    monitor->mandar_paquete_objetos(posicion_objetos);
    if (muerto != 0)
    {
        respawnear_gusano(muerto);
    }
}

void Escenario::avisar_desconexion(int jugador)
{
    if (jugador == monitor->recibir_turno())
    {
        monitor->cambiar_turno();
    };
    monitor->avisar_desconexion();
    std::map<int, Gusano *> &gusanosJugador = gusanos[jugador];
    // Liberar la memoria de los gusanos del jugador
    for (auto &pair : gusanosJugador)
    {
        delete pair.second;
    }
    // Borrar el mapa de gusanos del jugador
    gusanos.erase(jugador);
    mandar_paquete();
}

void Escenario::respawnear_gusano(int jugador_id)
{
    int spawnIndex = rand() % spawns.size();
    b2Vec2 spawn(spawns[spawnIndex].first, spawns[spawnIndex].second);
    spawns.erase(spawns.begin() + spawnIndex);
    Gusano *nuevo_gusano = new Gusano(mundo, spawn, jugador_id);
    // Crear un nuevo gusano
    std::map<int, Gusano *> nuevoGusanos;
    nuevoGusanos[1] = nuevo_gusano;
    gusanos[jugador_id] = nuevoGusanos;
    int movimiento = true;
    while (movimiento)
    {
        mundo->paso(FRAME_RATE, 6, 2);
        mandar_paquete();
        movimiento = en_movimiento();
    }
    mandar_paquete();
}

void Escenario::agregar_gusano(int jugador_id)
{
    int spawnIndex = rand() % spawns.size();
    b2Vec2 spawn(spawns[spawnIndex].first, spawns[spawnIndex].second);
    spawns.erase(spawns.begin() + spawnIndex);
    Gusano *nuevo_gusano = new Gusano(mundo, spawn, jugador_id);
    // Crear un nuevo gusano
    std::map<int, Gusano *> nuevoGusanos;
    nuevoGusanos[1] = nuevo_gusano;
    gusanos[jugador_id] = nuevoGusanos;
    monitor->mandar_escenario(x_size, y_size, vigas, jugador_id);
    mandar_paquete();
    int movimiento = true;
    while (movimiento)
    {
        mundo->paso(FRAME_RATE, 6, 2);
        mandar_paquete();
        movimiento = en_movimiento();
    }
    mandar_paquete();
}

void Escenario::colocar_viga(int x, int y, bool tipo, int angulo_grados)
{
    float_t angulo = angulo_grados * (M_PI / 180);
    int largo;
    if (tipo)
    {
        largo = 60;
    }
    else
    {
        largo = 30;
    }
    mundo->agregar_viga(x, y, largo, angulo);
    // Calcular los puntos por encima de la viga y guárdalos en spawns
    float_t incrementoX = cos(angulo) * 0.5f;      // Incremento en la dirección X
    float_t incrementoY = abs(sin(angulo) * 0.5f); // Incremento en la dirección Y
    float_t puntoX = x + 1.0f;                     // Iniciar en la parte superior de la viga
    float_t puntoY = y + 8.0f + 10.0;

    while (puntoX < x + largo - 2.0f)
    {
        spawns.push_back(std::make_pair(static_cast<int>(puntoX), static_cast<int>(puntoY + 1.0)));
        puntoX += incrementoX;
        puntoY += incrementoY;
    }
    PosicionViga posicion_viga(tipo, x, y, angulo_grados + 45);
    vigas.push_back(posicion_viga);
}

void Escenario::mover_gusano_derecha(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento();
        }
        mundo->paso(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_derecha();
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        if (gusano_a_mover and gusano_a_mover->daño_recibido())
        {
            monitor->cambiar_turno();
            break;
        }
        mandar_paquete();
    }
    mandar_paquete();
}

void Escenario::mover_gusano_izquierda(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento();
        }
        mundo->paso(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_izquierda();
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        if (gusano_a_mover and gusano_a_mover->daño_recibido())
        {
            monitor->cambiar_turno();
            break;
        }
        mandar_paquete();
    }
    mandar_paquete();
}

void Escenario::mover_gusano_arriba_adelante(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento();
        }
        mundo->paso(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_arriba_adelante();
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        if (gusano_a_mover and gusano_a_mover->daño_recibido())
        {
            monitor->cambiar_turno();
            break;
        }
        mandar_paquete();
    }
    mandar_paquete();
}

void Escenario::mover_gusano_arriba_atras(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento();
        }
        mundo->paso(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_arriba_atras();
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        if (gusano_a_mover and gusano_a_mover->daño_recibido())
        {
            monitor->cambiar_turno();
            break;
        }
        mandar_paquete();
    }

    mandar_paquete();
}

void Escenario::equipar_arma(int gusano, int jugador, int arma)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    int ammo = gusano_a_mover->cambiar_arma(arma);
    monitor->mandar_arma(jugador, arma, ammo);
}

void Escenario::usar_arma(int gusano, int jugador, Arma *arma)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    bool arma_usada = gusano_a_mover->usar_arma(arma, objetos);
    bool movimiento = true;
    while (movimiento and arma_usada)
    {
        mundo->paso(FRAME_RATE, 6, 2);
        mandar_paquete();
        movimiento = en_movimiento();
    }
    if (gusano_a_mover)
    {
        gusano_a_mover->daño_recibido();
    }
    if (arma != nullptr)
    {
        delete arma;
    }
    if (arma_usada)
    {
        monitor->cambiar_turno();
    }
}

Escenario::~Escenario()
{
    // Limpiar el vector de spawns
    delete mundo;

    // Limpiar el vector de objetos
    if (objetos != nullptr)
    {
        for (Objeto *objeto : *objetos)
        {
            delete objeto;
        }
        delete objetos;
    }

    // No olvides liberar la memoria de los Gusano*
    for (auto &pair : gusanos)
    {
        for (auto &inner_pair : pair.second)
        {
            delete inner_pair.second;
        }
    }
    spawns.clear();
    gusanos.clear();
}
