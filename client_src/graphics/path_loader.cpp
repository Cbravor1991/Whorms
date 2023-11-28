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

    sprite_path.push_back("/sprites/Weapon/In-game/airmisil.png");
    sprite_path.push_back("/sprites/Weapon/In-game/dynamite.png");
    sprite_path.push_back("/sprites/Weapon/In-game/bzkmisil.png");
    sprite_path.push_back("/sprites/Weapon/In-game/mortar.png");
    sprite_path.push_back("/sprites/Weapon/In-game/grenade.png");
    sprite_path.push_back("/sprites/Weapon/In-game/cgrenade.png");
    sprite_path.push_back("/sprites/Weapon/In-game/hgrenade.png");
    sprite_path.push_back("/sprites/Weapon/In-game/banana.png");

    sprite_path.push_back("/sprites/Weapon/Icons/banana.1.png");
    sprite_path.push_back("/sprites/Weapon/Worm/mortar/wbaz2.png");
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
    sprite_path.push_back("/Effects/potencia/blob.png");
    sprite_path.push_back("/Effects/explosion/circle50.png");
    sprite_path.push_back("/Effects/explosion/elipse75.png");
    sprite_path.push_back("/Effects/explosion/expow.png");
    sprite_path.push_back("/sprites/misc/crates/wcrate0.png");
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
    sounds_path.push_back("/sonidos/Explosion1.wav");
}