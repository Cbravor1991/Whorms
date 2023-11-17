

#ifndef ATAQUEAEREO_H_
#define ATAQUEAEREO_H_

#include <string>
#include <map>
#include <vector>
#include <optional>
#include "common_jugadorDTO.h"


class AtaqueAereo
{
private:
    int pos_x_seleccionado_ataque;
    int pos_y_seleccionado_ataque;
    int pos_x_explosion;
    int pos_y_explosion;
    int danio;
    int radio_danio;


public:
    AtaqueAereo();
    ~AtaqueAereo();

    void cargar_pos_x_seleccionada();
    void cargar_pos_y_seleccionada();
    void obtener_pos_x_seleccionada ();
    void obtener_pos_y_seleccionada ();

    void cargar_pos_x_explosión();
    void cargar_pos_y_explosion();

    void obtener_pos_x_explosion ();
    void obtener_pos_y_explosion ();

   


    



};

#endif //  CLIENT_H_
