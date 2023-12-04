#include "configuracion_mapa.h"
#include <fstream>
#include <iostream>

ConfiguracionMapa& ConfiguracionMapa::obtener_configuracion_mapa(std::string path) {
    static ConfiguracionMapa configuracion_mapa(YAML::LoadFile(path));
    return configuracion_mapa;
}

ConfiguracionMapa::ConfiguracionMapa(const YAML::Node& node) : vigas(), fondo(node["fondo"]["pantalla"].as<int>()), spawns_automaticos(node["spawns_automaticos"].as<int>())
     {
        const YAML::Node viga = node["vigas"];
        if (viga && viga.IsSequence()) {
            for (const auto& nodo_viga : viga) {
                PosicionViga posicion_viga(nodo_viga["tipo"].as<int>(), 
                nodo_viga["x"].as<int>(),
                nodo_viga["y"].as<int>(),
                nodo_viga["angulo"].as<int>());

                vigas.push_back(posicion_viga);
            }
        }
        if (!spawns_automaticos) {
            const YAML::Node spawn = node["spawns_mapa"];
            if (spawn && spawn.IsSequence()) {
                for (const auto& nodo_spawn : viga) {
                    PosicionSpawn posicion_spawn( 
                    nodo_spawn["x"].as<int>(),
                    nodo_spawn["y"].as<int>());

                    spawns.push_back(posicion_spawn);
                }
            }
        }
     }

std::vector<PosicionViga> ConfiguracionMapa::getVigas() const {
    return vigas;
}

std::vector<PosicionSpawn> ConfiguracionMapa::getSpawns() const {
    return spawns;
}

int ConfiguracionMapa::getFondo() const {
    return fondo;
}

bool ConfiguracionMapa::getSpawnsAutomaticos() const {
    return spawns_automaticos;
}

ConfiguracionMapa::~ConfiguracionMapa() {}