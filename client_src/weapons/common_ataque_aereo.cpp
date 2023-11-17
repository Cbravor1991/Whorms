#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <thread>

#include <chrono>
#include <SDL2pp/SDL2pp.hh>

#include "common_ataque_aereo.h"

using namespace SDL2pp;

AtaqueAereo::AtaqueAereo()
{
    nombre = "ataque aéreo";
}

std::string AtaqueAereo::obtener_nombre() {
    return nombre;
}

AtaqueAereo::~AtaqueAereo() {

}