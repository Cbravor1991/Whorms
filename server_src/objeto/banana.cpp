#include "banana.h"
#include <string>

Banana::Banana(bool direccion, int angulo, int segundos, int potencia)
{
    this->angulo = angulo * (M_PI / 180);
    tiempo_hasta_explotar = segundos;
    fuerza = std::pow(potencia, FUERZA_LANZAMIENTO);
    if (!direccion)
    {
        fuerza = -std::pow(potencia, FUERZA_LANZAMIENTO);
    }
}

Banana::Banana(Mundo *mundo, b2Body *cuerpo, int segundos)
{
    tiempo_hasta_explotar = segundos;
    esperando_a_explotar = true;
    this->mundo = mundo;
    body = cuerpo;
    danio = configuracion.getDanioBanana();
    radio = 40;
    velocidad_minima = 1.2f;
}

int Banana::disparar(Mundo *mundo, b2Body *disparador)
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
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 5;
    body->CreateFixture(&fixtureDef);
    b2Vec2 linear_velocity(fuerza * cos(angulo + disparador->angle),
                           abs(fuerza) * sin(angulo + disparador->angle));
    body->ApplyLinearImpulse(linear_velocity, body->GetWorldCenter(), true);
    Objeto *banana = new Banana(mundo, body, tiempo_hasta_explotar);
    mundo->agregar_objeto(banana);
    return 0;
}

PosicionLanzable Banana::conseguir_posicion()
{
    contacto();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA or contactos > 200)
    {
        is_dead = true;
    }

    float angle_radians = (float) atan2((double) body->GetLinearVelocity().y, (double) body->GetLinearVelocity().x);
    int angulo = (int) (angle_radians * (180.0f/M_PI));
    if (angulo < 0) 
    {
        angulo = 360 + angulo;
    }
    return PosicionLanzable(BANANA, x, y, 0, angulo, is_dead);
}

void Banana::explotar_regresiva()
{
    b2Vec2 center = this->body->GetPosition();
    explotar(center);
    is_dead = true;
}

void Banana::contacto()
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

Banana::~Banana() {}
