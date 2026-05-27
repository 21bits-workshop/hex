#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#ifndef POPUP_MESSAGE_H
#define POPUP_MESSAGE_H

class PopupMessage {
public:
  PopupMessage(int startX, int startY, int width, int height, char *message,
               std::function<void()> handleKeys, TTF_Font *font);

  void render(SDL_Renderer *renderer);
  void run();

private:
  TTF_Font *font;
  int startX, startY;
  int width, height;
  char *message;
  std::function<void()> handleKeys;
};
#endif
