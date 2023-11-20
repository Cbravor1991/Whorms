#include "path_loader.h"


PathLoader::PathLoader() {

    this->loadSpritePath();

}

std::vector<std::string>& PathLoader::getSpritePath() {
    return sprite_path;
}

std::string& PathLoader::getBackgroundPath(){
    return background_path;
}

std::string& PathLoader::getMusicPath() {
    return music_path;
}


void PathLoader::loadSpritePath() {
    //pushear los path relativos desde la carpeta data para
    //que se carguen y se creen las texturas
    sprite_path.push_back("/sprites/worm/walk/wwalk.png");
    sprite_path.push_back("/sprites/vigas/grdl4.png");
    sprite_path.push_back("/sprites/vigas/grds4.png");
    sprite_path.push_back("/sprites/Weapon/Icons/airmisil.png");
    sprite_path.push_back("/sprites/Weapon/Icons/banana.1.png");

}

void PathLoader::loadBackgroundPath() {
    //para varios fondos o elementos para hacer el fondo, transformar en vector
    //a background_path y usar un map(como el de los sprites, en texture_manager)
    background_path = "/sprites/escenario.png";
}

void PathLoader::loadMusicPath() {
    //para varias canciones, transformar en vector a music_path
    // y usar un map(como el de los sprites, en texture_manager)
    music_path = "/sonidos/worms_music.mp3";
}
