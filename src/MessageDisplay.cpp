#include "MessageDisplay.h"
#include "Colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

MessageDisplay::MessageDisplay(TTF_Font *font) : font(font) {}

void MessageDisplay::updateMessages(const std::vector<std::string> &messages) {
  activeMessages = messages;
}

void MessageDisplay::render(SDL_Renderer *renderer, int x, int y) {
  int currentY = y;
  for (const auto &msg : activeMessages) {
    SDL_Surface *surface =
        TTF_RenderText_Blended(font, msg.c_str(), Colors::mocha_textWhite);
    if (surface) {
      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
      if (texture) {
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        SDL_Rect destRect = {x, currentY, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        currentY += h + 2; // Add a small bit of spacing.
        SDL_DestroyTexture(texture);
      }
      SDL_FreeSurface(surface);
    }
  }
}
