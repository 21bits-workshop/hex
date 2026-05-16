#ifndef WORLD_DISP_H
#define WORLD_DISP_H

#include "Map.h"
#include <SDL2/SDL_ttf.h>
#include <map>
#include <utility>
#include <vector>

class WorldDisplay {
public:
  WorldDisplay(TTF_Font *font);

  void draw(SDL_Renderer *renderer, const Map &map, int startX, int startY,
            int tileSize);
  void updateMapTexture(SDL_Renderer *renderer, const Map &map, int tileSize);
  void invalidate();

private:
  int width;    // Width in Tiles
  int height;   // Height in Tiles
  int tileSize; // Size in pixels
  TTF_Font *font;
  SDL_Texture *m_cachedMapTexture = nullptr;
  std::map<std::pair<char, SDL_Color>, SDL_Surface *> m_charSurfaceCache;
};

#endif // WORLD_DISP_H
