#include "texture_manager.h"

TextureManager::TextureManager() {}


void TextureManager::loadTexture(SDL2pp::Renderer& renderer) {

    
    std::vector<std::string>& sprite_path_vector = assests.getSpritePath();
    
    for (std::string sprite : sprite_path_vector)
    { 
        std::string datapath(DATA_PATH);
        SDL2pp::Texture tex(renderer, SDL2pp::Surface(datapath.append(sprite)));

        this->sprites[sprite] = std::make_shared<SDL2pp::Texture>(std::move(tex));
    }
   
}

void TextureManager::loadBackground(SDL2pp::Renderer& renderer) {
    SDL2pp::Texture fondo(renderer, DATA_PATH "/sprites/escenario.png");
    this->background = std::make_shared<SDL2pp::Texture>(std::move(fondo));
}

void TextureManager::loadMusic() {
    SDL2pp::Music musica_fondo(DATA_PATH "/sonidos/worms_music.mp3");
    this->music = std::make_shared<SDL2pp::Music>(std::move(musica_fondo));

}


std::shared_ptr<SDL2pp::Texture> TextureManager::getTexture(std::string sprite_path) {
    return this->sprites.at(sprite_path);
}

std::shared_ptr<SDL2pp::Texture> TextureManager::getBackground() {
    return this->background;
}

std::shared_ptr<SDL2pp::Music> TextureManager::getMusic() {
    return this->music;
}