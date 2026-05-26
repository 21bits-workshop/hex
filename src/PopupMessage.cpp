#include "PopupMessage.h"
#include "Colors.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>

PopupMessage::PopupMessage(int startX, int startY, int width, int height,
                           char *message,
                           std::function<void(SDL_Event &e)> handleKey,
                           TTF_Font *font, SDL_Renderer *renderer) {
  SDL_Surface *popupSurface =
      SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  SDL_Surface *popupText = TTF_RenderText_Blended(font, message, Colors::white);
  SDL_Rect textDestRect = {0, 0, 0, 0};
  SDL_Rect popupDestRect = {startX, startY, width, height};
  SDL_BlitSurface(popupText, NULL, popupSurface, &textDestRect);

  SDL_Texture *messageTexture =
      SDL_CreateTextureFromSurface(renderer, popupSurface);
  SDL_RenderCopy(renderer, messageTexture, NULL, &popupDestRect);
  SDL_RenderPresent(renderer);
  SDL_Event popupEvent;
  while (SDL_PollEvent(&popupEvent) != 0) {
    handleKey(popupEvent);
  }
  SDL_DestroyTexture(messageTexture);

  SDL_FreeSurface(popupSurface);
  SDL_FreeSurface(popupText);
}
