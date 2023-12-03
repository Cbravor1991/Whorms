#ifndef WHORMS_H_
#define WHORMS_H_

#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;





class Whorms
{
private:
   
public:
    Whorms();
    ~Whorms();
    Texture loadSprite(Renderer& render, std::string path);
    int renderizar(Renderer& renderer,  Texture& sprites); 
    bool is_running;
    bool estadoDelGusano();
    void seguirCorriendo();
    void dejarDeCorrer();

  
};

#endif //  CLIENT_H_
