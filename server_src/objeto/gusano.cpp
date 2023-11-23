#include "gusano.h"
#include "../inventario.cpp"
#include <iostream>
#include <ostream>

Gusano::Gusano(Mundo *mundo, b2Vec2 spawn, int id_cliente, int id_gusano) : Objeto(mundo), inventario(), id_cliente(id_cliente), id_gusano(id_gusano)
{
    float_t squareSize = 1.0f;
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = spawn;
    body = mundo->crear_objeto(bd);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(squareSize * 0.5f, squareSize * 0.5f);
    b2FixtureDef fd;
    fd.shape = &boxShape;
    fd.density = 0.0f;
    fd.friction = 10.0f;
    fd.restitution = 0.0f;
    body->CreateFixture(&fd);
    direccion = 1;
    body->ApplyLinearImpulse(b2Vec2(0.0, -1.0), body->GetWorldCenter(), true);
    altura = spawn.y;
    body->angle = -1;
}

bool Gusano::usar_arma(Arma *arma, std::vector<Objeto *> *objetos)
{
    return inventario.disparar(mundo, body, arma, objetos);
}

std::pair<int, int> Gusano::cambiar_arma(int tipo)
{
    return std::make_pair(id_gusano, inventario.cambiar_arma(tipo));
}

void Gusano::mover_derecha()
{
    en_movimiento = true;
    float_t horizontalForce = CAMINAR * cos(angulo_viga);
    float_t verticalForce = CAMINAR * sin(angulo_viga);
    body->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), body->GetWorldCenter(), true); // AVANZO 0,2
    direccion = 1;
}

void Gusano::mover_izquierda()
{
    en_movimiento = true;
    float_t horizontalForce = (-1 * CAMINAR) * cos(angulo_viga);
    float_t verticalForce = (-1 * CAMINAR) * sin(angulo_viga);
    body->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), body->GetWorldCenter(), true); // AVANZO 0,2
    direccion = -1;
}

void Gusano::mover_arriba_adelante()
{
    en_movimiento = true;
    float_t horizontalForce;
    float_t verticalForce;
    if (angulo_viga > 10)
    {
        horizontalForce = direccion * SALTO_ADELANTE_X * std::abs(cos(angulo_viga));
        verticalForce = ((SALTO_ADELANTE_Y + body->GetMass() * 2) + (direccion)) * std::abs(sin(angulo_viga));
    }
    else if (angulo_viga < -10)
    {
        horizontalForce = direccion * SALTO_ADELANTE_X * std::abs(cos(angulo_viga));
        verticalForce = ((SALTO_ADELANTE_Y + body->GetMass() * 2) - (direccion)) * std::abs(sin(angulo_viga));
    }
    else
    {
        horizontalForce = direccion * SALTO_ADELANTE_X;
        verticalForce = SALTO_ADELANTE_Y;
    }
    body->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), body->GetWorldCenter(), true);
}

void Gusano::mover_arriba_atras()
{
    en_movimiento = true;
    float_t horizontalForce;
    float_t verticalForce;
    if (angulo_viga > 10)
    {
        horizontalForce = -1 * direccion * SALTO_ATRAS_X * std::abs(cos(angulo_viga));
        verticalForce = ((SALTO_ATRAS_Y + body->GetMass() * 2) + (-direccion)) * std::abs(sin(angulo_viga));
    }
    else if (angulo_viga < -10)
    {
        horizontalForce = -1 * direccion * SALTO_ATRAS_X * std::abs(cos(angulo_viga));
        verticalForce = ((SALTO_ATRAS_Y + body->GetMass() * 2) - (-direccion)) * std::abs(sin(angulo_viga));
    }
    else
    {
        horizontalForce = -1 * direccion * SALTO_ATRAS_X;
        verticalForce = SALTO_ATRAS_Y;
    }
    body->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), body->GetWorldCenter(), true);
}

int Gusano::getDireccion() { return direccion; }

PosicionLanzable Gusano::conseguir_posicion()
{
    return PosicionLanzable();
}

PosicionJugador Gusano::conseguir_posicion_gusano()
{
    cambiar_angulo_viga();
    int dire = direccion;
    b2Vec2 posicion = body->GetPosition();
    int angulo = (angulo_viga * (180 / M_PI)) + 45;
    std::cout << "X = " << posicion.x << ", Y = " << posicion.y << " vida: " << body->vida << std::endl;
    if (posicion.y > altura)
    {
        altura = posicion.y;
    }
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (dire == -1)
    {
        dire = 0;
    }
    if (y < ALTURA_AGUA or body->vida <= 0)
    {
        body->daniado = true;
        is_dead = true;
    }
    PosicionJugador posicion_jugador(id_cliente, id_gusano, x, y, dire, angulo, body->vida, en_movimiento);
    return posicion_jugador;
}

void Gusano::cambiar_angulo_viga()
{
    b2Contact *contact = mundo->recibir_contactos();
    while (contact != nullptr)
    {

        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        // Comprueba si uno de los cuerpos es el cuadrado
        if (fixtureA->GetBody() == body || fixtureB->GetBody() == body)
        {
            // Ahora necesitas determinar cuál es el otro body involucrado
            b2Body *otherBody = (fixtureA->GetBody() == body) ? fixtureB->GetBody() : fixtureA->GetBody();
            angulo_viga = otherBody->angle;
            b2Vec2 posicion = body->GetPosition();
            float caida = abs(altura - posicion.y);
            altura = posicion.y;
            if (caida > 30)
            {
                body->vida -= (caida - 20) / 10;
                body->daniado = true;
            }
        }
        contact = contact->GetNext();
    }
}

bool Gusano::daño_recibido()
{
    b2Vec2 posicion = body->GetPosition();
    if (posicion.y < ALTURA_AGUA or body->vida <= 0)
    {
        body->daniado = true;
        is_dead = true;
    }
    bool daño = body->daniado;
    body->daniado = false;
    return daño;
}
