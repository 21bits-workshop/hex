#ifndef STATUS_DISP_H
#define STATUS_DISP_H

#include <SDL2/SDL_ttf.h>

#include "Player.h"
#include <memory>
#include <utility>

class StatusDisplay {
public:
  StatusDisplay(TTF_Font *font);
  void updateDisplayTexture(SDL_Renderer *renderer, int tileSize,
                            std::shared_ptr<Player> player);

private:
  int width;
  int height;
  int tileSize;
  TTF_Font *font;

  SDL_Texture *m_statusDisplayTexture = nullptr;
};

#endif
