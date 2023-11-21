#ifndef WORM_IDLE_H
#define WORM_IDLE_H

#include "worm_status.h"


class WormIdle:public WormStatus {
    private:
    int animation_frame;
    int total_frames;
    std::vector<int> animation;
    
    public:
    explicit WormIdle();
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) override;
    const int getState() override;
    void reset_animation() override;
    void update_animation() override;
};


#endif
