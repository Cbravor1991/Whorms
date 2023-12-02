#include "bazooka.h"
#include <string>

Bazooka::Bazooka(bool direccion, int angulo, int potencia)
{

    this->angulo = angulo * (M_PI / 180);
    fuerza = std::pow(potencia, FUERZA_LANZAMIENTO);
    if (!direccion)
    {
        fuerza = -std::pow(potencia, FUERZA_LANZAMIENTO);
    }
}

Bazooka::Bazooka(Mundo *mundo, b2Body *cuerpo)
{
    this->mundo = mundo;
    body = cuerpo;
    danio = configuracion.getDanioBazooka();
    radio = configuracion.getRadioBazooka();
    velocidad_minima = 1.2f;
    float viento = mundo->recibir_velocidad_viento();
    body->ApplyLinearImpulse(b2Vec2(viento, 0.0), body->GetWorldCenter(), true);
}

int Bazooka::disparar(Mundo *mundo, b2Body *disparador)
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
    Objeto *bazooka = new Bazooka(mundo, body);
    mundo->agregar_objeto(bazooka);
    return 0;
}

void Bazooka::contacto_explosivo()
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
            contactos += 1;
            if (otherBody->gusano or contactos > 5)
            {
                b2Vec2 center = this->body->GetPosition();
                explotar(center);
                is_dead = true;
            }
        }
        contact = contact->GetNext();
    }
}

PosicionLanzable Bazooka::conseguir_posicion()
{
    contacto_explosivo();
    b2Vec2 posicion = body->GetPosition();
    int x = static_cast<int>(posicion.x);
    int y = static_cast<int>(posicion.y);
    if (y < ALTURA_AGUA or !consultar_movimiento())
    {
        is_dead = true;
    }

    float angle_radians = (float) atan2((double) body->GetLinearVelocity().y, (double) body->GetLinearVelocity().x);
    int angulo = (int) (angle_radians * (180.0f/M_PI));
    if (angulo < 0) 
    {
        angulo = 360 + angulo;
    }
    return PosicionLanzable(BAZOOKA, x, y, 0, angulo, is_dead);
}

Bazooka::~Bazooka() {}
