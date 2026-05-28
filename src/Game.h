/* Game.h
 * The Game class is a singleton that will contain everything related to game
 * state and execution. The only things that should exist outside of the Game
 * instance are: a) Structures that exist prior to the start of the game, eg.
 * main menu or title screen. b) Objects used by SDL,
 * and SDL initialization boilerplate.
 */

#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "MessageBuffer.h"
#include "MessageDisplay.h"
#include "Player.h"
#include "PlayerController.h"
#include "PopupMessage.h"
#include "StatusDisplay.h"
#include "WorldDisplay.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <string>

class Game {
public:
  Game();
  void run(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
  Map &getCurrentMap();
  Map &getOverworld() { return overworld; }
  Map &getReality() { return reality; }
  Map &getCyberspace() { return cyberspace; }
  void handleEvents(SDL_Event &e, SDL_Renderer *renderer, TTF_Font *font);
  void update(SDL_Event &e);
  void render(SDL_Renderer *renderer, WorldDisplay *display,
              SDL_Window *window);
  void switchMap(const std::string &type);
  std::shared_ptr<Player> getPlayer();
  MessageBuffer &getMessageBuffer() { return messageBuffer; }
  void updateFOV(int maxObstacles, int dx, int dy);
  void castLight(unsigned int x, unsigned int y, unsigned int row,
                 float startSlope, float endSlope, unsigned int xx,
                 unsigned int xy, unsigned int yx, unsigned int yy);
  void calculateFov(unsigned int x, unsigned int y);

private:
  // player and playerController will always be present.
  // so keep pointers pointing directly at them for easy access.
  std::shared_ptr<Player> player;
  std::shared_ptr<PlayerController> playerController;
  
  Map overworld; // A hard-coded overworld map. 
  Map reality;   // The reality map the player currently occupies.
  Map cyberspace; // The cyberspace map the player currently occupies.
  Map *currentMap; // The map the player is currently interacting with.
  SDL_Event event; // Holds the current keystroke.
  bool quit; // Has the program recieved the order to exit?
  bool isDirty; // Is the current game state dirty (i.e. needs rendering)?
  MessageBuffer messageBuffer; // Holds all game messages yet to be displayed by messageDisplay.
  PopupMessage *currentPopup; // Points to nullptr id if no popup. Otherwise, points to the popup to be resolved.
  WorldDisplay *worldDisplay; // Section of the screen thad displays the environment.
  MessageDisplay *messageDisplay; // Section of the screen that displays queued messages.
  StatusDisplay *statusDisplay; // Section of the screen that displays player/world info.
};

#endif // GAME_H
