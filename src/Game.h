/* Game.h
 * The Game class is a singleton that will contain everything related to game
 * state and execution. The only things that should exist outside of the Game
 * instance are: a) Structures that exist prior to the start of the game, eg.
 * main menu or title screen b) User interface elements. c) Objects used by SDL,
 * and SDL initialization boilerplate.
 */

#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "MessageBuffer.h"
#include "MessageDisplay.h"
#include "Player.h"
#include "PlayerController.h"
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
  // void run(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font,
  //          WorldDisplay &display);
  void run(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
  Map &getCurrentMap();
  Map &getOverworld() { return overworld; }
  Map &getReality() { return reality; }
  Map &getCyberspace() { return cyberspace; }
  void handleEvents(SDL_Event &e);
  void update();
  void render(SDL_Renderer *renderer, WorldDisplay *display,
              SDL_Window *window);
  void switchMap(const std::string &type);
  std::shared_ptr<Player> getPlayer();
  MessageBuffer &getMessageBuffer() { return messageBuffer; }

private:
  std::shared_ptr<Player> player;
  std::shared_ptr<PlayerController> playerController;
  Map overworld;
  Map reality;
  Map cyberspace;
  Map *currentMap;
  SDL_Event event;
  bool quit;
  bool isDirty;
  MessageBuffer messageBuffer;
  WorldDisplay *worldDisplay;
  MessageDisplay *messageDisplay;
  StatusDisplay *statusDisplay;
};

#endif // GAME_H
