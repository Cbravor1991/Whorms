#include "gusano.h"

Gusano::Gusano(b2Body *cuerpo)
{
    this->cuerpo = cuerpo;
    direccion = 1;
}

void Gusano::mover_derecha(b2Contact *contact)
{
    cambiar_angulo_viga(contact);
    float_t horizontalForce = CAMINAR * cos(angulo_viga);
    float_t verticalForce = CAMINAR * sin(angulo_viga);
    cuerpo->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), cuerpo->GetWorldCenter(), true); // AVANZO 0,2
    direccion = 1;
}

void Gusano::mover_izquierda(b2Contact *contact)
{
    cambiar_angulo_viga(contact);
    float_t horizontalForce = (-1 * CAMINAR) * cos(angulo_viga);
    float_t verticalForce = (-1 * CAMINAR) * sin(angulo_viga);
    cuerpo->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), cuerpo->GetWorldCenter(), true); // AVANZO 0,2
    direccion = -1;
}

void Gusano::mover_arriba_adelante(b2Contact *contact)
{
    float_t horizontalForce;
    float_t verticalForce;
    cambiar_angulo_viga(contact);
    if (direccion * angulo_viga > 0)
    {
        horizontalForce = direccion * SALTO_ADELANTE_X * cos(angulo_viga);
        verticalForce = (SALTO_ADELANTE_Y + cuerpo->GetMass()) * sin(angulo_viga);
    }
    else
    {
        horizontalForce = direccion * SALTO_ADELANTE_X;
        verticalForce = SALTO_ADELANTE_Y;
    }
    cuerpo->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), cuerpo->GetWorldCenter(), true);
}

void Gusano::mover_arriba_atras(b2Contact *contact)
{
    float_t horizontalForce;
    float_t verticalForce;
    cambiar_angulo_viga(contact);
    if (direccion * angulo_viga < 0)
    {
        horizontalForce = -1 * direccion * SALTO_ATRAS_X * cos(angulo_viga);
        verticalForce = (SALTO_ATRAS_Y + cuerpo->GetMass()) * sin(angulo_viga);
    }
    else
    {
        horizontalForce = -1 * direccion * SALTO_ATRAS_X;
        verticalForce = SALTO_ATRAS_Y;
    }
    cuerpo->ApplyLinearImpulse(b2Vec2(horizontalForce, verticalForce), cuerpo->GetWorldCenter(), true);
}

int Gusano::getDireccion() { return direccion; }

PosicionJugador Gusano::GetPosicion(int id)
{
    int dire = direccion;
    b2Vec2 posicion = cuerpo->GetPosition();
    // std::cout << "X = " << posicion.x << ", Y = " << posicion.y << std::endl;
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (dire == -1)
    {
        dire = 0;
    }
    PosicionJugador posicion_jugador(id, x, y, dire, angulo_viga);
    return posicion_jugador;
}

void Gusano::cambiar_angulo_viga(b2Contact *contact)
{
    while (contact != nullptr)
    {

        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        // Comprueba si uno de los cuerpos es el cuadrado
        if (fixtureA->GetBody() == cuerpo || fixtureB->GetBody() == cuerpo)
        {
            // Ahora necesitas determinar cuál es el otro cuerpo involucrado
            b2Body *otherBody = (fixtureA->GetBody() == cuerpo) ? fixtureB->GetBody() : fixtureA->GetBody();
            angulo_viga = otherBody->angle;
        }
        contact = contact->GetNext();
    }
}

b2Body *Gusano::getCuerpo() { return cuerpo; }