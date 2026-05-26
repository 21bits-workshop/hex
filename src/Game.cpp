#include "Game.h"
#include "Constants.h"
#include "MobileObject.h"
#include "Player.h"
#include "PopupMessage.h"
#include "StatusDisplay.h"
#include "WorldDisplay.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// TODO: Add section to display, world alerts, etc.

Game::Game()
    : overworld(
          Map::createWallMap(Constants::MAP_WIDTH, Constants::MAP_HEIGHT)),
      reality(Map::generateRoomAndHallwayMap(Constants::MAP_WIDTH,
                                             Constants::MAP_HEIGHT, 36, 6, 12)),
      cyberspace(Map::generateRoomAndHallwayMap(
          Constants::MAP_WIDTH, Constants::MAP_HEIGHT, 50, 5, 13)),
      quit(false), isDirty(true), messageBuffer() {
  player = std::make_shared<Player>(
      overworld.getPlayerStartX(), overworld.getPlayerStartY(),
      reality.getPlayerStartX(), reality.getPlayerStartY(),
      cyberspace.getPlayerStartX(), cyberspace.getPlayerStartY(), '@',
      const_cast<char *>("Takomo"), this);

  overworld.addEntity(player);
  reality.addEntity(player);
  cyberspace.addEntity(player);
  currentMap = &overworld;
  playerController = std::make_shared<PlayerController>(this);
}

void Game::run(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font) {
  worldDisplay = new WorldDisplay(font);
  messageDisplay = new MessageDisplay(font);
  statusDisplay = new StatusDisplay(font);

  while (!quit) {

    while (SDL_PollEvent(&event) != 0) {
      handleEvents(event, renderer, font);
      update(event);
      isDirty = true;
      worldDisplay->invalidate();
    }

    if (isDirty) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      render(renderer, worldDisplay, window);

      SDL_RenderPresent(renderer);
      worldDisplay->clearVisible(getCurrentMap());
      isDirty = false;
    }
  }
  delete worldDisplay;
  delete messageDisplay;
  delete statusDisplay;
}

void Game::handleEvents(SDL_Event &e, SDL_Renderer *renderer, TTF_Font *font) {
  if (e.type == SDL_QUIT) {
    quit = true;
  } else if (e.type == SDL_KEYDOWN) {
    isDirty = true;
    if (e.key.keysym.sym == SDLK_ESCAPE) {
      quit = true;
    } else if (e.key.keysym.sym == SDLK_t) {
      std::function<void(SDL_Event & funcEvent)> popupFunc =
          [](SDL_Event &funcEvent) {};
      PopupMessage(15, 120, 150, 150, const_cast<char *>("Test message"),
                   popupFunc, font, renderer);
    } else {
      messageBuffer.push(
          "You find yourself in a half-finished proof-of-concept. It's dark, "
          "empty, and rather boring. You doubt you will be eaten by a grue.");
    }
  }
}

void Game::update(SDL_Event &e) {
  auto messages = messageBuffer.popNextSix();
  if (!messages.empty()) {
    messageDisplay->updateMessages(messages);
  }
  for (const auto &ptr : currentMap->getEntities()) {
    if (ptr) {
      if (dynamic_cast<Player *>(ptr.get())) {
        playerController->handleInput(e);
      }
      if (dynamic_cast<MobileObject *>(ptr.get())) {
        MobileObject *mob = dynamic_cast<MobileObject *>(ptr.get());
        mob->update();
      }
    }
  }
}

void Game::render(SDL_Renderer *renderer, WorldDisplay *display,
                  SDL_Window *window) {
  calculateFov(player->getX(), player->getY());
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  int startX = (w - (Constants::MAP_WIDTH * Constants::TILE_SIZE)) / 2;
  int startY = 8 * Constants::TILE_SIZE;
  display->draw(renderer, *currentMap, startX, startY, Constants::TILE_SIZE);
  messageDisplay->render(renderer, 10, 10);
  statusDisplay->updateDisplayTexture(renderer, Constants::TILE_SIZE, player,
                                      this);
}

void Game::switchMap(const std::string &type) {
  if (type == "overworld") {
    currentMap = &overworld;
  } else if (type == "reality") {
    currentMap = &reality;
  } else if (type == "cyberspace") {
    currentMap = &cyberspace;
  }
}

Map &Game::getCurrentMap() { return *currentMap; }
std::shared_ptr<Player> Game::getPlayer() { return player; }

void Game::castLight(unsigned int x, unsigned int y, unsigned int row,
                     float startSlope, float endSlope, unsigned int xx,
                     unsigned int xy, unsigned int yx, unsigned int yy) {
  if (startSlope < endSlope) {
    return;
  }
  float nextStartSlope = startSlope;
  for (int i = row; i <= Constants::SIGHT_RADIUS; i++) {
    bool isBlocked = false;
    for (int dx = -i, dy = -i; dx <= 0; dx++) {
      float lSlope = (dx - 0.5) / (dy + 0.5);
      float rSlope = (dx + 0.5) / (dy - 0.5);

      if (startSlope < rSlope) {
        continue;
      } else if (endSlope > lSlope) {
        break;
      }

      int sax = dx * xx + dy * xy;
      int say = dx * yx + dy * yy;

      if ((sax < 0 && (unsigned int)std::abs(sax) > x) ||
          (say < 0 && (unsigned int)std::abs(say) > y)) {
        continue;
      }
      unsigned int ax = x + sax;
      unsigned int ay = y + say;

      if (ax >= currentMap->getWidth() || ay >= currentMap->getHeight()) {
        continue;
      }

      unsigned int radiusSquared =
          Constants::SIGHT_RADIUS * Constants::SIGHT_RADIUS;

      if (dx * dx + dy * dy < radiusSquared) {
        currentMap->getSpace(ax, ay).setDiscovered(true);
        currentMap->getSpace(ax, ay).setVisible(true);
      }

      if (isBlocked) {
        if (currentMap->getSpace(ax, ay).blocksLOS()) {
          nextStartSlope = rSlope;
          continue;
        } else {
          isBlocked = false;
          startSlope = nextStartSlope;
        }
      } else if (currentMap->getSpace(ax, ay).blocksLOS()) {
        isBlocked = true;
        nextStartSlope = rSlope;
        castLight(x, y, i + 1, startSlope, lSlope, xx, xy, yx, yy);
      }
    }
    if (isBlocked) {
      break;
    }
  }
}

static int multipliers[4][8] = {{1, 0, 0, -1, -1, 0, 0, 1},
                                {0, 1, -1, 0, 0, -1, 1, 0},
                                {0, 1, 1, 0, 0, -1, -1, 0},
                                {1, 0, 0, 1, -1, 0, 0, -1}};

void Game::calculateFov(unsigned int x, unsigned int y) {
  for (unsigned int i = 0; i < 8; i++) {
    castLight(x, y, 1, 1.0, 0.0, multipliers[0][i], multipliers[1][i],
              multipliers[2][i], multipliers[3][i]);
  }
}
