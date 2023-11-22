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

int Escenario::cambiar_turno(int id)
{
    if (id != 0)
    {
        gusanos[id].cambiar_turno();
    }
    return monitor->cambiar_turno();
}

bool Escenario::en_movimiento()
{
    for (auto &par : gusanos)
    {
        TurnoGusano &turno = par.second;

        if (turno.consultar_movimiento())
        {
            return true;
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
    std::vector<PosicionJugador> posicion_totales;
    for (auto it = gusanos.begin(); it != gusanos.end();)
    {
        int clave = it->first;
        TurnoGusano &turno = it->second;

        std::vector<PosicionJugador> posiciones = turno.recibir_posiciones_gusanos();
        posicion_totales.insert(posicion_totales.end(), posiciones.begin(), posiciones.end());
        // Supongamos que decides eliminar el turno basándote en alguna condición
        if (turno.vacio())
        {
            monitor->eliminar_turno(clave);
            if (clave - 1 == monitor->recibir_turno())
            {
                monitor->cambiar_turno();
            };
            it = gusanos.erase(it);
        }
        else
        {
            ++it;
        }
    }
    monitor->mandar_paquete_gusanos(posicion_totales);
    std::vector<PosicionLanzable> posicion_objetos;
    for (auto it = objetos->begin(); it != objetos->end();)
    {
        PosicionLanzable objeto = (*it)->conseguir_posicion();
        posicion_objetos.push_back(objeto);
        if (!(*it)->esta_vivo())
        {
            // Si el objeto no está vivo, elimínalo del vector.
            it = objetos->erase(it);
        }
        else
        {
            ++it; // Solo incrementa el iterador si no eliminaste el objeto.
        }
    }
    monitor->mandar_paquete_objetos(posicion_objetos);
}

void Escenario::avisar_desconexion(int jugador)
{
    if (jugador == monitor->recibir_turno())
    {
        monitor->cambiar_turno();
    };
    monitor->avisar_desconexion();
    mandar_paquete();
}

void Escenario::respawnear_gusano(int jugador_id)
{
    gusanos[jugador_id].agregar_gusano(agregar_gusano(jugador_id, 1));
    int movimiento = true;
    while (movimiento)
    {
        mundo->paso(FRAME_RATE, 6, 2);
        mandar_paquete();
        movimiento = en_movimiento();
    }
    mandar_paquete();
}

Gusano *Escenario::agregar_gusano(int jugador_id, int gusano_id)
{
    int spawnIndex = rand() % spawns.size();
    b2Vec2 spawn(spawns[spawnIndex].first, spawns[spawnIndex].second);
    spawns.erase(spawns.begin() + spawnIndex);
    Gusano *nuevo_gusano = new Gusano(mundo, spawn, jugador_id, gusano_id);
    return nuevo_gusano;
}

void Escenario::agregar_jugador(int jugador_id)
{
    gusanos[jugador_id].agregar_gusano(agregar_gusano(jugador_id, 1));
    gusanos[jugador_id].agregar_gusano(agregar_gusano(jugador_id, 2));
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

void Escenario::mover_gusano_derecha(int jugador)
{
    Gusano *gusano_a_mover = gusanos[jugador].recibir_turno();
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
            gusanos[jugador].cambiar_turno();
            monitor->cambiar_turno();
            break;
        }
        mandar_paquete();
    }
    mandar_paquete();
    mandar_paquete();
}

void Escenario::mover_gusano_izquierda(int jugador)
{
    Gusano *gusano_a_mover = gusanos[jugador].recibir_turno();
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
            gusanos[jugador].cambiar_turno();
            monitor->cambiar_turno();
            break;
        }
        mandar_paquete();
    }
    mandar_paquete();
    mandar_paquete();
}

void Escenario::mover_gusano_arriba_adelante(int jugador)
{
    Gusano *gusano_a_mover = gusanos[jugador].recibir_turno();
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
            gusanos[jugador].cambiar_turno();
            monitor->cambiar_turno();
            break;
        }
        mandar_paquete();
    }
    mandar_paquete();
    mandar_paquete();
}

void Escenario::mover_gusano_arriba_atras(int jugador)
{
    Gusano *gusano_a_mover = gusanos[jugador].recibir_turno();
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
            gusanos[jugador].cambiar_turno();
            break;
        }
        mandar_paquete();
    }
    mandar_paquete();
    mandar_paquete();
}

void Escenario::equipar_arma(int jugador, int arma)
{
    std::pair<int, int> id_y_ammo = std::make_pair(0, 0);
    if (arma != -1)
    {
        Gusano *gusano_a_mover = gusanos[jugador].recibir_turno();
        id_y_ammo = gusano_a_mover->cambiar_arma(arma);
    }
    monitor->mandar_arma(jugador, id_y_ammo.first, arma, id_y_ammo.second);
}

void Escenario::usar_arma(int jugador, Arma *arma)
{
    Gusano *gusano_a_mover = gusanos[jugador].recibir_turno();
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
        gusanos[jugador].cambiar_turno();
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

    spawns.clear();
    gusanos.clear();
}
