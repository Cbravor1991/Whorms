#include <vector>
#include "texture_manager.h"


class Explotion {

    private:
    int x;
    int y;
    bool fin;
    // int animation_frame;
    // int total_frames;
    // std::vector<int> animation;
    //cada componente de la animacion debe ser para cada animacion
    //ver de agregar el radio de la explosion? para que dependiendo de eso sea mas grande o no
    int cant_iteraciones = 0;
    public:

    explicit Explotion(int pos_x, int pos_y);

    void renderizar(SDL2pp::Renderer& renderer, TextureManager& tex_manager);

    bool finalizo();

};
