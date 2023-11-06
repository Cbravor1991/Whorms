

#ifndef COMMON_STATE_GAME_H_
#define COMMON_STATE_GAME_H_

#include <string>
#include <map>
#include <vector>

class StateGame
{

public:
    int type;
    
    StateGame() {}
    virtual void cambiar_render(bool &permiso) {}
    virtual ~StateGame() {}
};

#endif
