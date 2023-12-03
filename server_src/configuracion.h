#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <yaml-cpp/yaml.h>
#include <cstdint>

class Configuracion {

private:
   
    int vida_gusano;
    int tiempo_turno_gusano;
    float velocidad_gusano;
    int salto_enter_adelante_gusano;  
    float salto_enter_alto_gusano;
    float salto_return_atras_gusano; 
    float salto_return_alto_gusano;

    int danio_bazooka;
    int radio_bazooka;

    int municiones_mortero;
    int danio_mortero;
    int radio_mortero;
    int radio_fragmento_mortero;
    int cant_fragmentos_mortero;

    //int municiones_granada_verde;
    int danio_granada_verde;
    int radio_granada_verde;

    int municiones_granada_santa;
    int danio_granada_santa;
    int radio_granada_santa;

    int municiones_dinamita;
    int danio_dinamita;
    int radio_dinamita;
    
    int danio_bate_baseball;
    int radio_bate_baseball;

    int municiones_granada_roja;
    int danio_granada_roja;
    int radio_granada_roja;
    int danio_fragmento_granada_roja;
    int radio_fragmento_granada_roja;
    int cant_fragmentos_granada_roja;

    int municiones_banana;
    int danio_banana;
    int radio_banana;

    int municiones_ataque_aereo;
    int danio_ataque_aereo;
    int radio_ataque_aereo;

    int cantidad_provisiones;
    int vida_extra_provisiones;
    int danio_provisiones;
    int radio_provisiones;

    Configuracion(const YAML::Node& node);

public:

    static Configuracion& obtener_configuracion();

    int getVidaGusano() const;
    int getTiempoTurnoGusano() const;
    float getVelocidadGusano() const;
    int getSaltoEnterAdelanteGusano() const;
    float getSaltoEnterAltoGusano() const;
    float getSaltoReturnAtrasGusano() const;
    float getSaltoReturnAltoGusano() const;

    int getDanioBazooka() const;
    int getRadioBazooka() const;

    int getMunicionesMortero() const;
    int getDanioMortero() const;
    int getRadioMortero() const;
    int getRadioFragmentoMortero() const;
    int getCantFragmentosMortero() const;

    //int getMunicionesGranadaVerde() const;
    int getDanioGranadaVerde() const;
    int getRadioGranadaVerde() const;

    int getMunicionesGranadaSanta() const;
    int getDanioGranadaSanta() const;
    int getRadioGranadaSanta() const;

    int getMunicionesDinamita() const;
    int getDanioDinamita() const;
    int getRadioDinamita() const;

    int getDanioBateBaseball() const;
    int getRadioBateBaseball() const;

    int getMunicionesGranadaRoja() const;
    int getDanioGranadaRoja() const;
    int getRadioGranadaRoja() const;
    int getDanioFragmentoGranadaRoja() const;
    int getRadioFragmentoGranadaRoja() const;
    int getCantFragmentosGranadaRoja() const;
    
    int getMunicionesBanana() const;
    int getDanioBanana() const;
    int getRadioBanana() const;

    int getMunicionesAtaqueAereo() const;
    int getDanioAtaqueAereo() const;
    int getRadioAtaqueAereo() const;

    int getCantidadProvisiones() const;
    int getVidaExtraProvisiones() const;
    int getDanioProvisiones() const;
    int getRadioProvisiones() const;

    Configuracion(const Configuracion&) = delete;
    Configuracion& operator=(const Configuracion&) = delete;

    ~Configuracion();
};


#endif  // CONFIGURACION_H_
