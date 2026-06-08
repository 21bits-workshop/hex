#include "PopupMessage.h"
#include "Colors.h"
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>

PopupMessage::PopupMessage(int startX, int startY, int width, int height,
                           char *message, std::function<void()> handleKeys,
                           TTF_Font *font)
    : startX(startX), startY(startY), width(width), height(height),
      message(message), handleKeys(handleKeys), font(font) {}

void PopupMessage::render(SDL_Renderer *renderer) {
  SDL_Surface *popupSurface =
      SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  SDL_Rect popupSurfaceDestRect = {0, 0, 0, 0};
  SDL_SetSurfaceBlendMode(popupSurface, SDL_BLENDMODE_BLEND);
  SDL_SetSurfaceAlphaMod(popupSurface, 128);

  SDL_Surface *popupText =
      TTF_RenderText_Blended(font, message, Colors::mocha_textWhite);
  SDL_Rect textDestRect = {0, 0, 0, 0};

  SDL_Texture *popupTexture =
      SDL_CreateTextureFromSurface(renderer, popupSurface);
  SDL_Rect popupDestRect = {startX, startY, width, height};
  SDL_RenderCopy(renderer, popupTexture, NULL, &popupDestRect);

  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, popupText);
  int textW, textH;
  SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
  SDL_Rect popupTextRect = {startX + 2, startY + 2, textW, textH};
  SDL_RenderCopy(renderer, textTexture, NULL, &popupTextRect);

  SDL_DestroyTexture(textTexture);
  SDL_DestroyTexture(popupTexture);
  SDL_FreeSurface(popupText);
  SDL_FreeSurface(popupSurface);
}

void PopupMessage::run() { handleKeys(); }
