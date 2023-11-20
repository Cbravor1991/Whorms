#ifndef WORM_WALK_H
#define WORM_WALK_H


#include "worm_status.h"
#include <vector>
class WormWalk: protected WormStatus {
    
    private:
    //std::shared_ptr<SDL2pp::Texture> texture;
    int animation_frame;
    int total_frames;
    std::vector<int> animation;
    public:
    explicit WormWalk();
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, bool direccion, int angulo) override;
    const int getState() override;
    void reset_animation() override;
    void update_animation() override;


};

#endif
