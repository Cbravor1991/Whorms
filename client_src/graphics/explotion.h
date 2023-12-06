#include <vector>
#include "texture_manager.h"


class Explotion {

    private:
    int x;
    int y;
    bool fin;
    int cant_iteraciones = 0;
    public:

    explicit Explotion(int pos_x, int pos_y);

    void renderizar(SDL2pp::Renderer& renderer, TextureManager& tex_manager);

    bool finalizo();

};
