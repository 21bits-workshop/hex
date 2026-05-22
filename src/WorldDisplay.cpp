#include "WorldDisplay.h"
#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include <string>

WorldDisplay::WorldDisplay(TTF_Font *font)
    : width(Constants::MAP_WIDTH), height(int(Constants::MAP_HEIGHT)),
      tileSize(Constants::TILE_SIZE), font(font) {}

void WorldDisplay::updateMapTexture(SDL_Renderer *renderer, Map &map,
                                    int tileSize) {
  if (m_cachedMapTexture) {
    SDL_DestroyTexture(m_cachedMapTexture);
    m_cachedMapTexture = nullptr;
  }

  SDL_Surface *mapSurface = SDL_CreateRGBSurfaceWithFormat(
      0, width * tileSize, height * tileSize, 32, SDL_PIXELFORMAT_RGBA32);
  SDL_FillRect(mapSurface, nullptr, SDL_MapRGB(mapSurface->format, 0, 0, 0));

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (map.isWithinBounds(x, y)) {
        const Space &space = map.getSpace(x, y);
        char character = space.getDisplayCharacter();
        SDL_Color fgColor = space.getCharacterColor();

        SDL_Color red = {255, 0, 0, 255}; // for testing LOS.

        std::string text(1, character);
        SDL_Surface *charSurface = nullptr;
        if (space.isDiscovered() && space.isVisible()) {
          charSurface = TTF_RenderText_Blended(font, text.c_str(), red);
        } else if (space.isDiscovered()) {
          charSurface = TTF_RenderText_Blended(font, text.c_str(), fgColor);
        }
        if (charSurface) {
          SDL_Rect destRect = {x * tileSize + (tileSize - charSurface->w) / 2,
                               (y * tileSize + (tileSize - charSurface->h) / 2),
                               charSurface->w, charSurface->h};
          SDL_BlitSurface(charSurface, nullptr, mapSurface, &destRect);
          SDL_FreeSurface(charSurface);
        }
      }
    }
  }
  clearVisible(map);

  m_cachedMapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
  SDL_FreeSurface(mapSurface);
}

void WorldDisplay::clearVisible(Map &map) {
  for (int y = 0; y < map.getHeight(); ++y) {
    for (int x = 0; x < map.getWidth(); ++x) {
      map.getSpace(x, y).setVisible(false);
    }
  }
}

void WorldDisplay::invalidate() {
  if (m_cachedMapTexture) {
    SDL_DestroyTexture(m_cachedMapTexture);
    m_cachedMapTexture = nullptr;
  }
}

void WorldDisplay::draw(SDL_Renderer *renderer, Map &map, int startX,
                        int startY, int tileSize) {
  if (m_cachedMapTexture == nullptr) {
    updateMapTexture(renderer, map, tileSize);
  }

  if (m_cachedMapTexture) {
    SDL_Rect destRect = {startX, startY, width * tileSize, height * tileSize};
    SDL_RenderCopy(renderer, m_cachedMapTexture, nullptr, &destRect);
  }

  for (const auto &entity : map.getEntities()) {
    int ex = entity->getX();
    int ey = entity->getY();
    if (ex >= 0 && ex < width && ey >= 0 && ey < height) {
      char character = entity->getDisplayCharacter();
      SDL_Color fgColor = entity->getFgColor();
      std::string text(1, character);
      SDL_Surface *charSurface =
          TTF_RenderText_Shaded(font, text.c_str(), fgColor, {0, 0, 0, 0});
      if (charSurface) {
        SDL_Rect destRect = {
            startX + ex * tileSize + (tileSize - charSurface->w) / 2,
            (startY + ey * tileSize + (tileSize - charSurface->h) / 2),
            charSurface->w, charSurface->h};
        SDL_Texture *texture =
            SDL_CreateTextureFromSurface(renderer, charSurface);
        if (texture) {
          SDL_RenderCopy(renderer, texture, nullptr, &destRect);
          SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(charSurface);
      }
    }
  }
}
