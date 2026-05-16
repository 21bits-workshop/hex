#include "Constants.h"
#include "Game.h"
#include "WorldDisplay.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL! Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  if (TTF_Init() == -int(1)) {
    std::cerr << "Could not initialize SDL_TTF! Error: " << TTF_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Project Hex", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, 0, 0,
                                        SDL_WINDOW_FULLSCREEN_DESKTOP);

  if (!window) {
    std::cerr << "Could not create window! Error: " << SDL_GetError()
              << std::endl;
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Could not create renderer! Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  TTF_Font *font = TTF_OpenFont(Constants::FONT_PATH, Constants::TILE_SIZE);
  if (!font) {
    std::cerr << "Failed to load font! Error: " << TTF_GetError() << std::endl;
  }

  // Global Objects
  Game game;

  // TODO: Add a title screen/main menu.

  // Main Loop
  game.run(window, renderer, font);

  if (font) {
    TTF_CloseFont(font);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
