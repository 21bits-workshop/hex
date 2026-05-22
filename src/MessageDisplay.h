/* MessageDisplay.h
 * The MessageDisplay class defines an area at the top of the screen which will
 * display messages emitted by the game and various entities, which are all
 * stored in a MessageBuffer.
 */
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
