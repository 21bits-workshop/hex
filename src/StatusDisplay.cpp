#include "StatusDisplay.h"
#include "Constants.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

StatusDisplay::StatusDisplay(TTF_Font *font)
    : width(Constants::MAP_WIDTH), height(Constants::TILE_SIZE * 6),
      tileSize(Constants::TILE_SIZE), font(font) {}

void StatusDisplay::updateDisplayTexture(SDL_Renderer *renderer, int tileSize,
                                         std::shared_ptr<Player> player) {
  if (m_statusDisplayTexture) {
    SDL_DestroyTexture(m_statusDisplayTexture);
    m_statusDisplayTexture = nullptr;
  }
  SDL_Surface *textSurface =
      TTF_RenderText_Blended(font, player->getName(), {255, 255, 255, 255});
  if (textSurface) {
    SDL_Texture *displayTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);
    int w, h;
    SDL_QueryTexture(displayTexture, NULL, NULL, &w, &h);
    SDL_Rect destRect = {Constants::TILE_SIZE,
                         (Constants::TILE_SIZE * 8 +
                          Constants::TILE_SIZE * Constants::MAP_HEIGHT +
                          Constants::TILE_SIZE),
                         w, h};
    SDL_RenderCopy(renderer, displayTexture, NULL, &destRect);
    SDL_DestroyTexture(displayTexture);
  }
  SDL_FreeSurface(textSurface);
}
