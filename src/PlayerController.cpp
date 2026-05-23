#include "PlayerController.h"
#include "Game.h"
#include "Player.h"
#include <SDL2/SDL_events.h>
#include <iostream>
#include <string>

PlayerController::PlayerController(Game *game) : game(game) {}

void PlayerController::handleInput(SDL_Event e) {
  if (e.type == SDL_KEYDOWN) {
    if (e.key.keysym.sym == SDLK_q) {
      std::string newWorldType;
      if (&game->getCurrentMap() == &game->getOverworld()) {
        game->switchMap("reality");
        newWorldType = "reality";
      } else if (&game->getCurrentMap() == &game->getReality()) {
        game->switchMap("cyberspace");
        newWorldType = "cyberspace";
      } else if (&game->getCurrentMap() == &game->getCyberspace()) {
        game->switchMap("overworld");
        newWorldType = "overworld";
      }

      if (!newWorldType.empty()) {
        game->getPlayer()->syncActiveCoordinates(newWorldType.c_str());
      }
    } else {
      int dx = 0;
      int dy = 0;
      if (e.key.keysym.sym == SDLK_UP)
        dy = -1;
      else if (e.key.keysym.sym == SDLK_DOWN)
        dy = 1;
      else if (e.key.keysym.sym == SDLK_LEFT)
        dx = -1;
      else if (e.key.keysym.sym == SDLK_RIGHT)
        dx = 1;

      if (dx != 0 || dy != 0) {
        Map &currentMap = game->getCurrentMap();
        Player *player = game->getPlayer().get();
        int newX = 0;
        int newY = 0;

        if (&currentMap == &game->getOverworld()) {
          newX = player->getOverworldX() + dx;
          newY = player->getOverworldY() + dy;
          if (currentMap.isWithinBounds(newX, newY) &&
              currentMap.getSpace(newX, newY).isTraversable()) {
            player->setOverworldX(newX);
            player->setOverworldY(newY);
          }
        } else if (&currentMap == &game->getReality()) {
          newX = player->getRealityX() + dx;
          newY = player->getRealityY() + dy;
          if (currentMap.isWithinBounds(newX, newY) &&
              currentMap.getSpace(newX, newY).isTraversable()) {
            player->setRealityX(newX);
            player->setRealityY(newY);
          }
        } else if (&currentMap == &game->getCyberspace()) {
          newX = player->getCyberspaceX() + dx;
          newY = player->getCyberspaceY() + dy;
          if (currentMap.isWithinBounds(newX, newY) &&
              currentMap.getSpace(newX, newY).isTraversable()) {
            player->setCyberspaceX(newX);
            player->setCyberspaceY(newY);
          }
        }

        if (&currentMap == &game->getOverworld()) {
          player->syncActiveCoordinates("overworld");
        } else if (&currentMap == &game->getReality()) {
          player->syncActiveCoordinates("reality");
        } else if (&currentMap == &game->getCyberspace()) {
          player->syncActiveCoordinates("cyberspace");
        }
      }
    }
  }
}

void PlayerController::update() {
  std::cout << "Running update..." << std::endl;
}

Game *PlayerController::getGame() const { return game; }
