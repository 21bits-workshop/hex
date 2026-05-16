#ifndef MESSAGE_DISPLAY_H
#define MESSAGE_DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

class MessageDisplay {
public:
  MessageDisplay(TTF_Font *font);
  void updateMessages(const std::vector<std::string> &messages);
  void render(SDL_Renderer *renderer, int x, int y);

private:
  TTF_Font *font;
  std::vector<std::string> activeMessages;
};

#endif // MESSAGE_DISPLAY_H
