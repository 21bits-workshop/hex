#include "Game.h"
#include "Constants.h"
#include "Player.h"
#include "StatusDisplay.h"
#include "WorldDisplay.h"
#include <string>

// TODO: Add section to display current world, world alerts, etc.

Game::Game()
    : overworld(Map::generateRoomAndHallwayMap(
          Constants::MAP_WIDTH, Constants::MAP_HEIGHT, 42, 5, 15)),
      reality(Map::generateRoomAndHallwayMap(Constants::MAP_WIDTH,
                                             Constants::MAP_HEIGHT, 36, 6, 12)),
      cyberspace(Map::generateRoomAndHallwayMap(
          Constants::MAP_WIDTH, Constants::MAP_HEIGHT, 50, 5, 13)),
      quit(false), isDirty(true), messageBuffer(), messageDisplay(nullptr) {
  player = std::make_shared<Player>(
      overworld.getPlayerStartX(), overworld.getPlayerStartY(),
      reality.getPlayerStartX(), reality.getPlayerStartY(),
      cyberspace.getPlayerStartX(), cyberspace.getPlayerStartY(), '@',
      const_cast<char *>("Takomo"));

  overworld.addEntity(player);
  reality.addEntity(player);
  cyberspace.addEntity(player);
  currentMap = &overworld;
  playerController = std::make_shared<PlayerController>(this);
}

void Game::run(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font
               /* WorldDisplay &display*/) {
  worldDisplay = new WorldDisplay(font);
  messageDisplay = new MessageDisplay(font);
  statusDisplay = new StatusDisplay(font);

  while (!quit) {
    while (SDL_PollEvent(&event) != 0) {
      handleEvents(event);
      isDirty = true;
      worldDisplay->invalidate();
    }

    update();

    if (isDirty) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      render(renderer, worldDisplay, window);

      SDL_RenderPresent(renderer);
      isDirty = false;
    }
  }
  delete messageDisplay;
  delete statusDisplay;
}

void Game::handleEvents(SDL_Event &e) {
  if (e.type == SDL_QUIT) {
    quit = true;
  } else if (e.type == SDL_KEYDOWN) {
    isDirty = true;
    if (e.key.keysym.sym == SDLK_ESCAPE) {
      quit = true;
    } else {
      playerController->handleInput(e);
      messageBuffer.push(
          "You find yourself in a half-finished proof-of-concept. It's dark, "
          "empty, and rather boring. You doubt you will be eaten by a grue.");
    }
  }
}

void Game::update() {
  auto messages = messageBuffer.popNextSix();
  if (!messages.empty()) {
    messageDisplay->updateMessages(messages);
  }
}

void Game::render(SDL_Renderer *renderer, WorldDisplay *display,
                  SDL_Window *window) {
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
