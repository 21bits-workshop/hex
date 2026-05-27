#include "PopupMessage.h"
#include "Colors.h"
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
  SDL_Surface *popupText = TTF_RenderText_Blended(font, message, Colors::white);
  SDL_Rect textDestRect = {0, 0, 0, 0};
  SDL_BlitSurface(popupText, NULL, popupSurface, &textDestRect);

  SDL_Texture *messageTexture =
      SDL_CreateTextureFromSurface(renderer, popupSurface);
  SDL_Rect popupDestRect = {startX, startY, width, height};
  SDL_RenderCopy(renderer, messageTexture, NULL, &popupDestRect);

  SDL_DestroyTexture(messageTexture);
  SDL_FreeSurface(popupText);
  SDL_FreeSurface(popupSurface);
}

void PopupMessage::run() { handleKeys(); }
