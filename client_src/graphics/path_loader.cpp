#include "path_loader.h"


PathLoader::PathLoader() {

    this->loadSpritePath();
    this->loadSoundsPath();
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

std::vector<std::string>& PathLoader::getSoundsPath() {
    return sounds_path;
}

void PathLoader::loadSpritePath() {
    //pushear los path relativos desde la carpeta data para
    //que se carguen y se creen las texturas
    sprite_path.push_back("/sprites/worm/walk/wwalk.png");
    sprite_path.push_back("/sprites/vigas/grdl4.png");
    sprite_path.push_back("/sprites/vigas/grds4.png");
    sprite_path.push_back("/sprites/Weapon/Icons/airmisil.png");
    sprite_path.push_back("/sprites/Weapon/Icons/banana.1.png");
    sprite_path.push_back("/sprites/Weapon/Worm/airStrike/wairlnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/teleport/wtellnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/banana/wbanlnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/bat/wbsblnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/bazooka/wbazlnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/dynamite/wdynlnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/clusterGrenade/wclslnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/holyGrenade/whgrlnk.png");
    sprite_path.push_back("/sprites/Weapon/Worm/grenade/wgrnlnk.png");
    sprite_path.push_back("/sprites/crshairr.png");


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

void PathLoader::loadSoundsPath() {
    sounds_path.push_back("/sonidos/salto.WAV");
    sounds_path.push_back("/sonidos/ataque misiles.wav");
    sounds_path.push_back("/sonidos/teletransportar.WAV");
}