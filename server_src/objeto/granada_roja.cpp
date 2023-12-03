#include "granada_roja.h"
#include <string>

GranadaRoja::GranadaRoja(bool direccion, int angulo, int segundos, int potencia)
{
    this->angulo = angulo * (M_PI / 180);
    tiempo_hasta_explotar = segundos;
    this->angulo = angulo * (M_PI / 180);
    fuerza = std::pow(potencia, FUERZA_LANZAMIENTO);
    if (!direccion)
    {
        fuerza = -std::pow(potencia, FUERZA_LANZAMIENTO);
    }
}

GranadaRoja::GranadaRoja(Mundo *mundo, b2Body *cuerpo, int segundos)
{
    tiempo_hasta_explotar = segundos;
    esperando_a_explotar = true;
    this->mundo = mundo;
    body = cuerpo;
    danio = configuracion.getDanioGranadaRoja();
    radio = configuracion.getRadioGranadaRoja();
    velocidad_minima = 1.2f;
}

int GranadaRoja::disparar(Mundo *mundo, b2Body *disparador)
{
    this->mundo = mundo;
    b2Vec2 posicion = disparador->GetPosition();
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    b2Vec2 spawn(posicion.x, posicion.y + 20);
    bd.position = spawn;
    b2Body *body = mundo->crear_objeto(bd);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(TAMANIO_X_BOMBA, TAMANIO_Y_BOMBA);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = DENSIDAD_BOMBA;
    fixtureDef.friction = 5.0f;
    body->CreateFixture(&fixtureDef);
    b2Vec2 linear_velocity(fuerza * cos(angulo + disparador->angle),
                           abs(fuerza) * abs(sin(angulo + disparador->angle)));
    body->ApplyLinearImpulse(linear_velocity, body->GetWorldCenter(), true);
    Objeto *granada_santa = new GranadaRoja(mundo, body, tiempo_hasta_explotar);
    mundo->agregar_objeto(granada_santa);
    return 1;
}

PosicionLanzable GranadaRoja::conseguir_posicion()
{
    // contacto();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA)
    {
        is_dead = true;
    }
    float angle_radians = (float) atan2((double) body->GetLinearVelocity().y, (double) body->GetLinearVelocity().x);
    int angulo = (int) (angle_radians * (180.0f/M_PI));
    if (angulo < 0) 
    {
        angulo = 360 + angulo;
    }
    return PosicionLanzable(CLUSTER_GRENADE, x, y, 0, angulo, is_dead);
}

void GranadaRoja::explotar_regresiva()
{
    b2Vec2 center = this->body->GetPosition();
    explotar(center);
    mandar_fragmentos(configuracion.getDanioFragmentoGranadaRoja(), configuracion.getRadioFragmentoGranadaRoja(), configuracion.getCantFragmentosGranadaRoja(), CLUSTER_GRENADE);
    is_dead = true;
}

void GranadaRoja::contacto()
{
    b2Contact *contact = mundo->recibir_contactos();
    while (contact != nullptr)
    {

        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        // Comprueba si uno de los cuerpos es el cuadrado
        if (fixtureA->GetBody() == body || fixtureB->GetBody() == body)
        {
            b2Body *otherBody = (fixtureA->GetBody() == body) ? fixtureB->GetBody() : fixtureA->GetBody();
            if (otherBody->gusano)
            {
                b2Vec2 center = this->body->GetPosition();
                explotar(center);
                is_dead = true;
            }
        }
        contact = contact->GetNext();
    }
}

GranadaRoja::~GranadaRoja() {}
