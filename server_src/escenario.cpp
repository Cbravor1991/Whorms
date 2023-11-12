#include "escenario.h"
#include <sstream>
#include "monitor_jugador.h"
#include "gusano.cpp"

bool en_movimiento(b2World *world)
{
    for (b2Body *cuerpo = world->GetBodyList(); cuerpo; cuerpo = cuerpo->GetNext())
    {
        // Comprueba la velocidad lineal y angular del cuerpo.
        b2Vec2 velocidadLineal = cuerpo->GetLinearVelocity();
        float velocidadAngular = cuerpo->GetAngularVelocity();

        // Define una velocidad mínima para considerar que el cuerpo está en movimiento.
        float velocidadMinima = 0.0f; // Ajusta este valor según tus necesidades.

        if (velocidadLineal.Length() > velocidadMinima || std::abs(velocidadAngular) > velocidadMinima)
        {
            return true; // Al menos un cuerpo está en movimiento.
        }
    }
    return false; // Ningún cuerpo está en movimiento.
}

Escenario::Escenario(std::uint16_t x_size, std::uint16_t y_size, MonitorJugadores *monitor) : x_size(x_size),
                                                                                              y_size(y_size), monitor(monitor)
{
    b2Vec2 gravity(0.0f, -10.0f);
    escenario = new b2World(gravity);
    escenario->SetContinuousPhysics(true);
    escenario->SetAllowSleeping(true);
    escenario->SetWarmStarting(true);
    escenario->SetSubStepping(false);
}

void Escenario::mandar_paquete()
{
    int gusano_id_muerto = -1;
    std::vector<PosicionJugador> posicion_jugadores;
    for (const auto &fila : gusanos)
    {
        for (const auto &par : fila.second)
        {
            Gusano *gusano = par.second;
            // Supongamos que tienes un método en Gusano para obtener la posición
            PosicionJugador jugador = gusano->GetPosicion(fila.first);

            if (jugador.recibir_altura() < 60)
            {
                gusano_id_muerto = fila.first;
            }
            posicion_jugadores.push_back(jugador);
        }
    }
    monitor->mandar_paquete(posicion_jugadores);
    if (gusano_id_muerto != -1)
    {
        std::map<int, Gusano *> &gusanosJugador = gusanos[gusano_id_muerto];
        for (auto &pair : gusanosJugador)
        {
            escenario->DestroyBody(pair.second->getCuerpo());
            delete pair.second;
        }
        gusanos.erase(gusano_id_muerto);
        agregar_gusano(gusano_id_muerto);
    }
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
    mandar_paquete();
}

void Escenario::agregar_gusano(int jugador_id)
{
    float_t squareSize = 1.0f;

    // Selecciona un punto de inicio aleatorio de los spawns

    int spawnIndex = rand() % spawns.size();
    b2Vec2 spawnPoint(spawns[spawnIndex].first, spawns[spawnIndex].second);
    spawns.erase(spawns.begin() + spawnIndex);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = spawnPoint; // Inicializa el cuadrado en el punto seleccionado

    b2Body *body = escenario->CreateBody(&bd);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(squareSize * 0.5f, squareSize * 0.5f);

    b2FixtureDef fd;
    fd.shape = &boxShape;
    fd.density = 0.0f;
    fd.friction = 10.0f;
    fd.restitution = 0.0f;

    body->CreateFixture(&fd);
    Gusano *nuevo_gusano = new Gusano(body);
    // Crear un nuevo gusano
    std::map<int, Gusano *> nuevoGusanos;
    nuevoGusanos[1] = nuevo_gusano;
    gusanos[jugador_id] = nuevoGusanos;

    monitor->mandar_escenario(x_size, y_size, vigas, jugador_id);
    mandar_paquete();
    int movimiento = true;
    while (movimiento)
    {
        escenario->Step(FRAME_RATE, 6, 2);
        mandar_paquete();
        movimiento = en_movimiento(escenario);
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
    float_t grosor = 8.0f;
    b2Body *viga = NULL;
    {

        b2BodyDef bd;
        viga = escenario->CreateBody(&bd);

        b2PolygonShape boxShape;
        float_t width = b2Distance(b2Vec2(x, y), b2Vec2(x + largo, y));
        float_t height = grosor;
        b2Vec2 center(x + largo * 0.5f, y + height * 0.45f);

        // Configurar la forma de la caja con un ángulo
        boxShape.SetAsBox(width * 0.5f, height * 0.5f, center, angulo);

        b2FixtureDef fd;
        fd.shape = &boxShape;
        fd.density = 0.01f;
        fd.friction = 1.0f; // Ajusta la fricción a un valor alto para hacerla pegajosa
        fd.restitution = 0.0f;

        viga->CreateFixture(&fd);
        viga->angle = angulo;
    }

    // Calcular los puntos por encima de la viga y guárdalos en spawns
    float_t incrementoX = cos(angulo) * 0.5f; // Incremento en la dirección X
    float_t incrementoY = sin(angulo) * 0.5f; // Incremento en la dirección Y
    float_t puntoX = x + 1.0f;                // Iniciar en la parte superior de la viga
    float_t puntoY = y + grosor + 1.0;

    while (puntoX < x + largo - 1.0f)
    {
        spawns.push_back(std::make_pair(static_cast<int>(puntoX), static_cast<int>(puntoY)));
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
    b2Contact *contact = escenario->GetContactList();
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento(escenario);
        }
        escenario->Step(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_derecha(contact);
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        mandar_paquete();
    }
    gusano_a_mover->cambiar_angulo_viga(contact);
}

void Escenario::mover_gusano_izquierda(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    b2Contact *contact = escenario->GetContactList();
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento(escenario);
        }
        escenario->Step(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_izquierda(contact);
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        mandar_paquete();
    }
    gusano_a_mover->cambiar_angulo_viga(contact);
}

void Escenario::mover_gusano_arriba_adelante(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    b2Contact *contact = escenario->GetContactList();
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento(escenario);
        }
        escenario->Step(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_arriba_adelante(contact);
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        mandar_paquete();
    }
    gusano_a_mover->cambiar_angulo_viga(contact);
}

void Escenario::mover_gusano_arriba_atras(int gusano, int jugador)
{
    std::map<int, Gusano *> &gusanosDelJugador = gusanos[jugador];
    Gusano *gusano_a_mover = gusanosDelJugador[gusano];
    b2Contact *contact = escenario->GetContactList();
    bool movimiento = true;
    bool impulseAplicado = false;
    while (movimiento)
    {
        if (impulseAplicado)
        {
            movimiento = en_movimiento(escenario);
        }
        escenario->Step(FRAME_RATE, 6, 2);
        if (!impulseAplicado)
        {
            gusano_a_mover->mover_arriba_atras(contact);
            impulseAplicado = true; // Marca que el impulso se ha aplicado
        }
        mandar_paquete();
    }
    gusano_a_mover->cambiar_angulo_viga(contact);
}

Escenario::~Escenario()
{

    // Limpiar el vector de spawns
    delete escenario;
    spawns.clear();
    gusanos.clear();
}
