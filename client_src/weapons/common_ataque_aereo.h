

#ifndef ATAQUEAEREO_H_
#define ATAQUEAEREO_H_

#include <string>
#include <map>
#include <vector>
#include <optional>
#include "../DTO/common_jugadorDTO.h"
#include "weapon.h"


class AtaqueAereo : public Weapon
{
private:
    std::string nombre;
    // int pos_x_seleccionado_ataque;
    // int pos_y_seleccionado_ataque;
    // int pos_x_explosion;
    // int pos_y_explosion;
    // int danio;
    // int radio_danio;


public:
    AtaqueAereo();
    ~AtaqueAereo();

    // void cargar_pos_x_seleccionada();
    // void cargar_pos_y_seleccionada();
    // void obtener_pos_x_seleccionada ();
    // void obtener_pos_y_seleccionada ();

    // void cargar_pos_x_explosion();
    // void cargar_pos_y_explosion();

    // void obtener_pos_x_explosion ();
    // void obtener_pos_y_explosion ();

    std::string obtener_nombre() override;

};

#endif //  CLIENT_H_
