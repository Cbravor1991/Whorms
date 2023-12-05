#ifndef CONFIGURACION_MAPA_H_
#define CONFIGURACION_MAPA_H_

#include <yaml-cpp/yaml.h>
#include <cstdint>
#include <string>
#include <vector>

#include "data/posicion_viga.h"
#include "data/posicion_spawn.h"

class ConfiguracionMapa
{

private:
    std::vector<PosicionViga> vigas;
    std::vector<PosicionSpawn> spawns;
    int fondo;
    bool spawns_automaticos;
    ConfiguracionMapa(const YAML::Node &node);

public:
    static ConfiguracionMapa obtener_configuracion_mapa(std::string path);

    std::vector<PosicionViga> getVigas() const;
    std::vector<PosicionSpawn> getSpawns() const;
    int getFondo() const;
    bool getSpawnsAutomaticos() const;
 

    ~ConfiguracionMapa();
};

#endif // CONFIGURACION_MAPA_H_
