#include "worm_weapon.h"

class WormTeleport : public WormWeapon {

    public:
    explicit WormTeleport();
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    ~WormTeleport() {}
};

