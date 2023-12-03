#include "configuracion.h"
#include <fstream>
#include <iostream>

Configuracion& Configuracion::obtener_configuracion() {
    static Configuracion configuracion(YAML::LoadFile(DATA_PATH "/configuracion.yaml"));
    return configuracion;
}

Configuracion::Configuracion(const YAML::Node& node) :
    vida_gusano(node["gusano"]["vida"].as<int>()),
    tiempo_turno_gusano(node["gusano"]["tiempo_turno"].as<int>()),
    velocidad_gusano(node["gusano"]["velocidad"].as<float>()),
    salto_enter_adelante_gusano(node["gusano"]["salto_enter_adelante"].as<int>()),
    salto_enter_alto_gusano(node["gusano"]["salto_enter_alto"].as<float>()),
    salto_return_atras_gusano(node["gusano"]["salto_return_atras"].as<float>()),
    salto_return_alto_gusano(node["gusano"]["salto_return_alto"].as<float>()),
    danio_bazooka(node["armas"]["bazooka"]["daño"].as<int>()),
    radio_bazooka(node["armas"]["bazooka"]["radio"].as<int>()),
    municiones_mortero(node["armas"]["mortero"]["municiones"].as<int>()),
    danio_mortero(node["armas"]["mortero"]["daño"].as<int>()),
    radio_mortero(node["armas"]["mortero"]["radio"].as<int>()),
    radio_fragmento_mortero(node["armas"]["mortero"]["radio_fragmento"].as<int>()),
    cant_fragmentos_mortero(node["armas"]["mortero"]["cant_fragmentos"].as<int>()),
    //municiones_granada_verde(node["armas"]["granada_verde"]["municiones"].as<int>()),
    danio_granada_verde(node["armas"]["granada_verde"]["daño"].as<int>()),
    radio_granada_verde(node["armas"]["granada_verde"]["radio"].as<int>()),
    municiones_granada_santa(node["armas"]["granada_santa"]["municiones"].as<int>()),
    danio_granada_santa(node["armas"]["granada_santa"]["daño"].as<int>()),
    radio_granada_santa(node["armas"]["granada_santa"]["radio"].as<int>()),
    municiones_dinamita(node["armas"]["dinamita"]["municiones"].as<int>()),
    danio_dinamita(node["armas"]["dinamita"]["daño"].as<int>()),
    radio_dinamita(node["armas"]["dinamita"]["radio"].as<int>()),
    danio_bate_baseball(node["armas"]["bate_baseball"]["daño"].as<int>()),
    radio_bate_baseball(node["armas"]["bate_baseball"]["radio"].as<int>()),
    municiones_granada_roja(node["armas"]["granada_roja"]["municiones"].as<int>()),
    danio_granada_roja(node["armas"]["granada_roja"]["daño"].as<int>()),
    radio_granada_roja(node["armas"]["granada_roja"]["radio"].as<int>()),
    danio_fragmento_granada_roja(node["armas"]["granada_roja"]["daño_fragmento"].as<int>()),
    radio_fragmento_granada_roja(node["armas"]["granada_roja"]["radio_fragmento"].as<int>()),
    cant_fragmentos_granada_roja(node["armas"]["granada_roja"]["cant_fragmentos"].as<int>()),
    municiones_banana(node["armas"]["banana"]["municiones"].as<int>()),
    danio_banana(node["armas"]["banana"]["daño"].as<int>()),
    radio_banana(node["armas"]["banana"]["radio"].as<int>()),
    municiones_ataque_aereo(node["armas"]["ataque_aereo"]["municiones"].as<int>()),
    danio_ataque_aereo(node["armas"]["ataque_aereo"]["daño"].as<int>()),
    radio_ataque_aereo(node["armas"]["ataque_aereo"]["radio"].as<int>()),
    cantidad_provisiones(node["provisiones"]["cantidad_provisiones"].as<int>()),
    vida_extra_provisiones(node["provisiones"]["vida"].as<int>()),
    danio_provisiones(node["provisiones"]["daño"].as<int>()),
    radio_provisiones(node["provisiones"]["radio"].as<int>()) {}

int Configuracion::getVidaGusano() const {
    return vida_gusano;
}

int Configuracion::getTiempoTurnoGusano() const {
    return tiempo_turno_gusano;
}

float Configuracion::getVelocidadGusano() const {
    return velocidad_gusano;
}

int Configuracion::getSaltoEnterAdelanteGusano() const {
    return salto_enter_adelante_gusano;
}

float Configuracion::getSaltoEnterAltoGusano() const {
    return salto_enter_alto_gusano;
}

float Configuracion::getSaltoReturnAtrasGusano() const {
    return salto_return_atras_gusano;
}

float Configuracion::getSaltoReturnAltoGusano() const {
    return salto_return_alto_gusano;
}

int Configuracion::getDanioBazooka() const {
    return danio_bazooka;
}

int Configuracion::getRadioBazooka() const {
    return radio_bazooka;
}

int Configuracion::getMunicionesMortero() const {
    return municiones_mortero;
}

int Configuracion::getDanioMortero() const {
    return danio_mortero;
}

int Configuracion::getRadioMortero() const {
    return radio_mortero;
}

int Configuracion::getRadioFragmentoMortero() const {
    return radio_fragmento_mortero;
}

int Configuracion::getCantFragmentosMortero() const {
    return cant_fragmentos_mortero;
}

// int Configuracion::getMunicionesGranadaVerde() const {
//     return municiones_granada_verde;
// }

int Configuracion::getDanioGranadaVerde() const {
    return danio_granada_verde;
}

int Configuracion::getRadioGranadaVerde() const {
    return radio_granada_verde;
}

int Configuracion::getMunicionesGranadaSanta() const {
    return municiones_granada_santa;
}

int Configuracion::getDanioGranadaSanta() const {
    return danio_granada_santa;
}

int Configuracion::getRadioGranadaSanta() const {
    return radio_granada_santa;
}

int Configuracion::getMunicionesDinamita() const {
    return municiones_dinamita;
}

int Configuracion::getDanioDinamita() const {
    return danio_dinamita;
}

int Configuracion::getRadioDinamita() const {
    return radio_dinamita;
}

int Configuracion::getDanioBateBaseball() const {
    return danio_bate_baseball;
}

int Configuracion::getRadioBateBaseball() const {
    return radio_bate_baseball;
}

int Configuracion::getMunicionesGranadaRoja() const {
    return municiones_granada_roja;
}

int Configuracion::getDanioGranadaRoja() const {
    return danio_granada_roja;
}

int Configuracion::getRadioGranadaRoja() const {
    return radio_granada_roja;
}

int Configuracion::getDanioFragmentoGranadaRoja() const {
    return danio_fragmento_granada_roja;
}

int Configuracion::getRadioFragmentoGranadaRoja() const {
    return radio_fragmento_granada_roja;
}

int Configuracion::getCantFragmentosGranadaRoja() const {
    return cant_fragmentos_granada_roja;
}

int Configuracion::getMunicionesBanana() const {
    return municiones_banana;
}

int Configuracion::getDanioBanana() const {
    return danio_banana;
}

int Configuracion::getRadioBanana() const {
    return radio_banana;
}

int Configuracion::getMunicionesAtaqueAereo() const {
    return municiones_ataque_aereo;
}

int Configuracion::getDanioAtaqueAereo() const {
    return danio_ataque_aereo;
}

int Configuracion::getRadioAtaqueAereo() const {
    return radio_ataque_aereo;
}

int Configuracion::getCantidadProvisiones() const {
    return cantidad_provisiones;
}

int Configuracion::getVidaExtraProvisiones() const {
    return vida_extra_provisiones;
}

int Configuracion::getDanioProvisiones() const {
    return danio_provisiones;
}

int Configuracion::getRadioProvisiones() const {
    return radio_provisiones;
}

Configuracion::~Configuracion() {}