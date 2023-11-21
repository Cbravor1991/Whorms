#include "worm_weapon.h"

class WormAirstike : public WormWeapon {

    public:
    explicit WormAirstike();
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    ~WormAirstike() {}
};
