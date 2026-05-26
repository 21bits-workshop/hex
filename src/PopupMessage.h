#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

class PopupMessage {
public:
  PopupMessage(int startX, int startY, int width, int height, char *message,
               std::function<void(SDL_Event &e)> handleKeys, TTF_Font *font,
               SDL_Renderer *renderer);

private:
  int startX, startY;
  int width, height;
  char *message;
  std::function<void(SDL_Event &e)> handleKeys;
};
