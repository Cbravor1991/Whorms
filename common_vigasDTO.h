#ifndef VIGASDTO_H_
#define VIGASDTO_H_

class VigasDTO
{
private:
    int x;
    int y;
    int id;
    bool tipo;

public:
    VigasDTO(); // Declaración del constructor

    void cargar_posicion_x(const int& posicion_x);
    void cargar_posicion_y(const int& posicion_y);
    void cargar_tipo(bool & tipo_viga);
    void cargar_id(const int& id_jugador);
    int obtener_posicion_x();
    int obtener_posicion_y();
    int obtener_posicion_id();
    bool obtener_tipo();
};

#endif // VIGASDTO_H_
