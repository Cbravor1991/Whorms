#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

#include "path_loader.h"
class TextureManager {

    private:
        PathLoader assests;
        std::map<std::string, std::shared_ptr<SDL2pp::Texture> > sprites;
        std::shared_ptr<SDL2pp::Music> music;
        std::shared_ptr<SDL2pp::Texture> background_night;
        std::shared_ptr<SDL2pp::Texture> background_snow;
        std::shared_ptr<SDL2pp::Texture> background;
        std::shared_ptr<SDL2pp::Texture> water;
        std::map<std::string, std::shared_ptr<SDL2pp::Chunk> > sonidos;

    public:

    explicit TextureManager();


    void loadTexture(SDL2pp::Renderer& renderer);
    void loadBackground(SDL2pp::Renderer& renderer);
    void loadWater(SDL2pp::Renderer& renderer);
    void loadBackgroundSnow(SDL2pp::Renderer& renderer);
    void loadBackgroundNight(SDL2pp::Renderer& renderer);
    void loadMusic();
    void loadSounds();

    std::shared_ptr<SDL2pp::Texture> getTexture(std::string texture_path);
    std::shared_ptr<SDL2pp::Texture> getBackground();
    std::shared_ptr<SDL2pp::Texture> getBackgroundNight();
    std::shared_ptr<SDL2pp::Texture> getBackgroundSnow();
    std::shared_ptr<SDL2pp::Music> getMusic();
    std::shared_ptr<SDL2pp::Chunk> getSound(std::string sound_path);
    std::shared_ptr<SDL2pp::Texture> getWater();  
};

#endif
