#include "escenario.h"
#include <sstream>
#include "monitor_jugador.h"
#include "data/posicion_objeto.h"

Escenario::Escenario(ConfiguracionMapa mapa)
{
    b2Vec2 gravity(0.0f, -10.0f);
    mundo = new Mundo(gravity);
    std::vector<PosicionViga> vigas = mapa.getVigas();
    for (const PosicionViga &viga : vigas)
    {
        colocar_viga(viga.obtener_x(), viga.obtener_y(), viga.obtener_tipo(), viga.obtener_angulo());
    }
    bool spawns_automaticos = mapa.getSpawnsAutomaticos();
    if (spawns_automaticos == 0)
    {
        agregar_spawns(mapa.getSpawns());
    }
}

void Escenario::iniciar(MonitorJugadores *monitor)
{
    this->monitor = monitor;
    for (int i = 0; i < configuracion.getCantidadProvisiones(); i++)
    {
        colocar_provision();
    }
}

Gusano *Escenario::recibir_gusano(int id)
{
    Gusano *gusano = nullptr;
    auto iter = gusanos.find(id);
    if (iter != gusanos.end())
    {
        gusano = iter->second.recibir_turno();
    }
    return gusano;
}

int Escenario::cambiar_turno(int id)
{
    if (id != 0 and gusanos.find(id) != gusanos.end())
    {
        gusanos[id].cambiar_turno();
    }
    int turno = monitor->cambiar_turno();
    if (turno != 0)
    {
        Gusano *gusano = gusanos[turno].recibir_turno();
        monitor->enviar_turno(gusano->conseguir_id());
    }
    VientoVelocidad viento = mundo->actualizar();
    monitor->mandar_viento(viento);
    return turno;
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
    if (mundo->en_movimiento())
    {
        return true;
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
                cambiar_turno(0);
            };
            it = gusanos.erase(it);
            if (gusanos.size() == 1)
            {
                monitor->enviar_ganador();
            }
        }
        else
        {
            ++it;
        }
    }
    monitor->mandar_paquete_gusanos(posicion_totales);
    std::vector<PosicionLanzable> posicion_objetos = mundo->recibir_posiciones_objetos();
    monitor->mandar_paquete_objetos(posicion_objetos);
}

void Escenario::avisar_desconexion(int jugador)
{
    if (jugador == monitor->recibir_turno())
    {
        cambiar_turno(0);
    };
    monitor->avisar_desconexion();
    gusanos.erase(jugador);
    mandar_paquete();
}

void Escenario::respawnear_gusano(int jugador_id)
{
    gusanos[jugador_id].agregar_gusano(agregar_gusano(jugador_id, 1));
    int movimiento = true;
    while (movimiento)
    {
        mundo->paso(FRAME_RATE, VELOCITY_ITERATION, POSITION_ITERATION);
        mandar_paquete();
        movimiento = en_movimiento();
    }
    mandar_paquete();
}

void Escenario::agregar_spawns(std::vector<PosicionSpawn> spawns_editor)
{
    spawns_mapa = spawns_editor;
    for (auto &par : spawns_mapa)
    {
        std::cout << par.obtener_x() << std::endl;
        std::cout << par.obtener_y() << std::endl;

        spawns.push_back(std::make_pair(static_cast<int>(par.obtener_x()), static_cast<int>(par.obtener_y() + 1.0)));
    }
}

Gusano *Escenario::agregar_gusano(int jugador_id, int gusano_id)
{
    int spawnIndex;

    // if (spawns_automaticos) {
    spawnIndex = rand() % spawns.size();
    b2Vec2 spawn(spawns[spawnIndex].first, spawns[spawnIndex].second);
    spawns.erase(spawns.begin() + spawnIndex);
    Gusano *nuevo_gusano = new Gusano(mundo, spawn, jugador_id, gusano_id);
    return nuevo_gusano;
    // } else {
    //     spawnIndex = rand() % spawns_personalizados.size();
    //     b2Vec2 spawn2(spawns_personalizados[spawnIndex].first, spawns_personalizados[spawnIndex].second);
    //     spawns_personalizados.erase(spawns_personalizados.begin() + spawnIndex);
    //     Gusano *nuevo_gusano = new Gusano(mundo, spawn2, jugador_id, gusano_id);
    //     return nuevo_gusano;
    // }
}

void Escenario::agregar_jugador(int jugador_id)
{
    bool vacio = false;
    if (gusanos.empty())
    {
        vacio = true;
    }
    for (int i = 1; i <= GUSANOS_POR_JUGADOR; ++i)
    {
        gusanos[jugador_id].agregar_gusano(agregar_gusano(jugador_id, i));
    }
    monitor->mandar_escenario(x_size, y_size, vigas, jugador_id);
    int movimiento = true;
    while (movimiento)
    {
        mundo->paso(FRAME_RATE, VELOCITY_ITERATION, POSITION_ITERATION);
        movimiento = en_movimiento();
    }
    mandar_paquete();
    if (vacio)
    {
        cambiar_turno(0);
    }
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
    float_t incrementoX = cos(angulo) * 3.0f;      // Incremento en la dirección X
    float_t incrementoY = abs(sin(angulo) * 3.0f); // Incremento en la dirección Y
    float_t puntoX = x + 8.0f + -angulo_grados * 0.3f;
    float_t puntoY = y + 12.0f + -angulo_grados * 0.3f;
    if (tipo) // Si es una viga larga
    {
        if (angulo_grados > 0)
        {
            puntoY += incrementoY * angulo_grados / 7;
            puntoX += incrementoX * angulo_grados / 7;
        }
        puntoX += incrementoX;
        puntoY += incrementoY;
        spawns.push_back(std::make_pair(static_cast<int>(puntoX), static_cast<int>(puntoY + 1.0)));
        puntoX += incrementoX * 10;
        puntoY += incrementoY * 10;
        spawns.push_back(std::make_pair(static_cast<int>(puntoX), static_cast<int>(puntoY + 1.0)));
    }
    else // Si es una viga chica
    {
        if (angulo_grados > 0)
        {
            puntoY += incrementoY * angulo_grados / 7;
            puntoX += incrementoX * angulo_grados / 7;
        }
        puntoX += incrementoX;
        puntoY += incrementoY;
        spawns.push_back(std::make_pair(static_cast<int>(puntoX), static_cast<int>(puntoY + 1.0)));
    }
    PosicionViga posicion_viga(tipo, x, y, angulo_grados + 45);
    vigas.push_back(posicion_viga);
}

void Escenario::colocar_provision()
{
    if (vigas.empty())
    {
        return;
    }

    int spawnIndex = rand() % spawns.size();
    b2Vec2 spawn(spawns[spawnIndex].first + 10, spawns[spawnIndex].second);
    int tipo_provision_random = rand() % 2;

    Objeto *provision = new Provision(mundo, tipo_provision_random, spawn.x, spawn.y);
    mundo->agregar_objeto(provision);
}

void Escenario::movimiento(Gusano *gusano, int jugador)
{
    bool danio = false;
    bool movimiento = true;
    while (movimiento)
    {
        movimiento = en_movimiento();
        mundo->paso(FRAME_RATE, VELOCITY_ITERATION, POSITION_ITERATION);
        if ((!danio) and gusano->danio_recibido())
        {
            cambiar_turno(jugador);
            danio = true;
        }
        mandar_paquete();
    }
    mandar_paquete();
    mandar_paquete();
}

void Escenario::mover_gusano_derecha(int jugador)
{
    Gusano *gusano_a_mover = recibir_gusano(jugador);
    if (gusano_a_mover != nullptr)
    {
        gusano_a_mover->mover_derecha();
        movimiento(gusano_a_mover, jugador);
    }
}

void Escenario::mover_gusano_izquierda(int jugador)
{
    Gusano *gusano_a_mover = recibir_gusano(jugador);
    if (gusano_a_mover != nullptr)
    {
        gusano_a_mover->mover_izquierda();
        movimiento(gusano_a_mover, jugador);
    }
}

void Escenario::mover_gusano_arriba_adelante(int jugador)
{
    Gusano *gusano_a_mover = recibir_gusano(jugador);
    if (gusano_a_mover != nullptr)
    {
        gusano_a_mover->mover_arriba_adelante();
        movimiento(gusano_a_mover, jugador);
    }
}

void Escenario::mover_gusano_arriba_atras(int jugador)
{
    Gusano *gusano_a_mover = recibir_gusano(jugador);
    if (gusano_a_mover != nullptr)
    {
        gusano_a_mover->mover_arriba_atras();
        movimiento(gusano_a_mover, jugador);
    }
}

void Escenario::equipar_arma(int jugador, int arma)
{
    Gusano *gusano_a_mover = recibir_gusano(jugador);
    std::pair<int, int> id_y_ammo = std::make_pair(0, 0);
    if (arma != -1 or gusano_a_mover != nullptr)
    {
        id_y_ammo = gusano_a_mover->cambiar_arma(arma);
    }
    monitor->mandar_arma(jugador, id_y_ammo.first, arma, id_y_ammo.second);
}

void Escenario::usar_arma(int jugador, Arma *arma)
{
    Gusano *gusano_a_mover = recibir_gusano(jugador);
    if (gusano_a_mover != nullptr)
    {
        bool arma_usada = gusano_a_mover->usar_arma(arma);
        bool movimiento = true;
        bool danio = false;
        while (movimiento and arma_usada)
        {
            mundo->paso(FRAME_RATE, VELOCITY_ITERATION, POSITION_ITERATION);
            movimiento = en_movimiento();
            if (!danio and gusano_a_mover->danio_recibido())
            {
                danio = true;
            }
            mandar_paquete();
        }
        if (arma_usada and (recibir_gusano(jugador) != nullptr and arma->cuenta_regresiva() == -1))
        {
            cambiar_turno(jugador);
            mandar_paquete();
        }
        mandar_paquete();
        if (arma != nullptr)
        {
            delete arma;
        }
    }
}

void Escenario::explotar_bombas_regresivas(int jugador)
{
    mundo->explotar_bombas_regresivas();
    while (en_movimiento())
    {
        mundo->paso(FRAME_RATE, VELOCITY_ITERATION, POSITION_ITERATION);
        mandar_paquete();
    }
    if (monitor->recibir_turno() == jugador)
    {
        cambiar_turno(jugador);
    }
    mandar_paquete();
    mandar_paquete();
}

Escenario::~Escenario()
{
    // Limpiar el vector de spawns
    gusanos.clear();
    delete mundo;
    spawns.clear();
}
