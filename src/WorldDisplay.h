/* WorldDisplay.h
 * The WorldDisplay object defines an area in the center of the screen where the
 * Player and their environment will be displayed. This contains the rendering
 * logic for actaully getting the map onscreen.
 */

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

  void draw(SDL_Renderer *renderer, Map &map, int startX, int startY,
            int tileSize);
  void updateMapTexture(SDL_Renderer *renderer, Map &map, int tileSize);
  void invalidate();
  void clearVisible(Map &map);

private:
  int width;    // Width in Tiles
  int height;   // Height in Tiles
  int tileSize; // Size in pixels
  TTF_Font *font;
  SDL_Texture *m_cachedMapTexture = nullptr;
};

#endif // WORLD_DISP_H
