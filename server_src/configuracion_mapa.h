#ifndef CONFIGURACION_MAPA_H_
#define CONFIGURACION_MAPA_H_

#include <yaml-cpp/yaml.h>
#include <cstdint>
#include <string>
#include <vector>

#include "data/posicion_viga.h"

class ConfiguracionMapa {

private:
   
    std::vector<PosicionViga> vigas;
    int fondo;
    bool spawns_automaticos;

    ConfiguracionMapa(const YAML::Node& node);

public:

    static ConfiguracionMapa& obtener_configuracion_mapa();

    std::vector<PosicionViga> getVigas() const;
    int getFondo() const;
    bool getSpawnsAutomaticos() const;

    ConfiguracionMapa(const ConfiguracionMapa&) = delete;
    ConfiguracionMapa& operator=(const ConfiguracionMapa&) = delete;

    ~ConfiguracionMapa();
};


#endif  // CONFIGURACION_MAPA_H_
