
#include <map>
#include <string>
#include <vector>
#include <SDL2pp/SDL2pp.hh>



class GameView {

    private://agregar mixer, ttf, etc
        SDL2pp::SDL sdl;
        SDL2pp::Window window;
        SDL2pp::Renderer renderer;
    public:

    explicit GameView();

    void mostrar();
    void clear();
    SDL2pp::Renderer& getRenderer();
};


