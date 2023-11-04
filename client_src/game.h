#include <string>
#include "client.h"
#include "graphics/view.h"

class Game {
    private:

    Cliente cliente;
    GameView view;

    public:

    //reemplazar por socket cuando este lobby
    explicit Game(const std::string &hostname, const std::string &servname);

    void run();

    bool gameLoop(StateGame *estado, bool &permiso);

    bool manejarEventos();
};

