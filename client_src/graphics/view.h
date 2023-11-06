
#include <map>
#include <string>
#include <vector>
#include <SDL2pp/SDL2pp.hh>



class GameView {

    private://agregar mixer, ttf, etc
        SDL2pp::SDL sdl;
        SDL2pp::Window window;
        SDL2pp::Renderer renderer;
        SDL2pp::SDLTTF ttf; //para render de letra
        
    public:

    explicit GameView();

    void mostrar();
    void clear();
    SDL2pp::Renderer& getRenderer();

    void renderizar_texto(const std::string texto, int pos_x, int pos_y);
};


