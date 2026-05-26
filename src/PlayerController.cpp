#include "PlayerController.h"
#include "Game.h"
#include "Player.h"
#include "PopupMessage.h"
#include <SDL2/SDL_events.h>
#include <iostream>
#include <string>

PlayerController::PlayerController(Game *game) : game(game) {}

void PlayerController::handleInput(SDL_Event e) {
  bool keyWasValid = false;
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
      keyWasValid = true;
    } else {
      int dx = 0;
      int dy = 0;
      if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_KP_8) {
        dy = -1;
        keyWasValid = true;
      } else if (e.key.keysym.sym == SDLK_DOWN ||
                 e.key.keysym.sym == SDLK_KP_2) {
        dy = 1;
        keyWasValid = true;
      } else if (e.key.keysym.sym == SDLK_LEFT ||
                 e.key.keysym.sym == SDLK_KP_4) {
        dx = -1;
        keyWasValid = true;
      } else if (e.key.keysym.sym == SDLK_RIGHT ||
                 e.key.keysym.sym == SDLK_KP_6) {
        dx = 1;
        keyWasValid = true;
      } else if (e.key.keysym.sym == SDLK_KP_7) {
        dx = -1;
        dy = -1;
        keyWasValid = true;
      } else if (e.key.keysym.sym == SDLK_KP_9) {
        dx = 1;
        dy = -1;
        keyWasValid = true;
      } else if (e.key.keysym.sym == SDLK_KP_1) {
        dx = -1;
        dy = 1;
        keyWasValid = true;
      } else if (e.key.keysym.sym == SDLK_KP_3) {
        dx = 1;
        dy = 1;
        keyWasValid = true;
      }

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
    if (!keyWasValid) {
      game->getMessageBuffer().push("Invalid command!");
    }
  }
}

void PlayerController::update() {
  std::cout << "Running update..." << std::endl;
}

Game *PlayerController::getGame() const { return game; }
