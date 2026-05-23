/* PlayerController.h
 *  The Player Controller is an ObjectController that uniquely belongs to the
 * Player object. In place of AI routines, it has a handleInput method that will
 * run when the game loop reaches the Player's turn.
 */
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "ObjectController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

class Game;

class PlayerController : public ObjectController {
public:
  PlayerController(Game *game);
  void handleInput(SDL_Event e);
  void update() override;

  Game *getGame() const;

private:
  Game *game;
};

#endif // PLAYER_CONTROLLER_H
