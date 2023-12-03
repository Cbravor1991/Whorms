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
    SDL2pp::Texture fondo(renderer, DATA_PATH "/sprites/lava_pattern.jpg");
    this->background = std::make_shared<SDL2pp::Texture>(std::move(fondo));
}

void TextureManager::loadBackgroundSnow(SDL2pp::Renderer& renderer) {
    SDL2pp::Texture fondo(renderer, DATA_PATH "/sprites/snow.jpg");
    this->background_snow = std::make_shared<SDL2pp::Texture>(std::move(fondo));
}


void TextureManager::loadBackgroundNight(SDL2pp::Renderer& renderer) {
    SDL2pp::Texture fondo(renderer, DATA_PATH "/sprites/night.jpg");
    this->background_night = std::make_shared<SDL2pp::Texture>(std::move(fondo));
}
  

void TextureManager::loadWater(SDL2pp::Renderer& renderer) {
    SDL2pp::Texture fondo(renderer, DATA_PATH "/sprites/water_pattern_2.png");
    this->water = std::make_shared<SDL2pp::Texture>(std::move(fondo));
}


void TextureManager::loadMusic() {
    SDL2pp::Music musica_fondo(DATA_PATH "/sonidos/worms_music.mp3");
    this->music = std::make_shared<SDL2pp::Music>(std::move(musica_fondo));

}

void TextureManager::loadSounds() {

    std::vector<std::string>& sounds_path_vector = assests.getSoundsPath();
    
    for (std::string sound : sounds_path_vector)
    { 
        std::string datapath(DATA_PATH);
        SDL2pp::Chunk sonido(datapath.append(sound));
        if(sound == "/sonidos/Explosion1.wav") {
            sonido.SetVolume(10);
        } else {
            sonido.SetVolume(25);
        }
        

        this->sonidos[sound] = std::make_shared<SDL2pp::Chunk>(std::move(sonido));
    }

    // SDL2pp::Chunk sonido(DATA_PATH "/sonidos/worms_music.mp3");
    // this->sonido = std::make_shared<SDL2pp::Chunk>(std::move(sonido));
 

}

std::shared_ptr<SDL2pp::Chunk> TextureManager::getSound(std::string sound_path) {
    return this->sonidos.at(sound_path);
}

std::shared_ptr<SDL2pp::Texture> TextureManager::getTexture(std::string sprite_path) {
    return this->sprites.at(sprite_path);
}

std::shared_ptr<SDL2pp::Texture> TextureManager::getBackground() {
    return this->background;
}

std::shared_ptr<SDL2pp::Texture> TextureManager::getBackgroundNight() {
    return this->background_night;
}

std::shared_ptr<SDL2pp::Texture> TextureManager::getBackgroundSnow() {
    return this->background_snow;
}

std::shared_ptr<SDL2pp::Music> TextureManager::getMusic() {
    return this->music;
}


std::shared_ptr<SDL2pp::Texture> TextureManager::getWater() {
    return this-> water;
}