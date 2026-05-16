#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <SDL2/SDL.h>

class Game;

class PlayerController {
public:
    PlayerController(Game* game);
    void handleInput(SDL_Event& e);

private:
    Game* game;
};

#endif // PLAYER_CONTROLLER_H
