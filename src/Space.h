/* Space.h
 * The Space class represents a single square map unit in the game
 * world - this is not to be confused with the Tile class, which represents
 * a unit of the *display*. It contains all information that would be relevant
 * to a game entity attempting to interact with or see the Space.
 */

#ifndef SPACE_H
#define SPACE_H

#include <SDL2/SDL.h>

class Space {
public:
  Space();
  Space(SDL_Color characterColor, char displayChar, bool traversable,
        bool blocksLOS, bool visible, bool discovered);

  void setCharacterColor(SDL_Color color);
  SDL_Color getCharacterColor() const;

  void setDisplayCharacter(char character);
  char getDisplayCharacter() const;

  void setTraversable(bool traversable);
  bool isTraversable() const;

  void setBlocksLOS(bool blocksLOS);
  bool blocksLOS() const;

  void setVisible(bool visible);
  bool isVisible() const;

  void setDiscovered(bool discovered);
  bool isDiscovered() const;

private:
  SDL_Color characterColor;
  char displayCharacter;
  bool traversable;
  bool blocksLOSValue; // Is the Space opaque?
  bool visible;        // Can the player *currently* see this Space?
  bool discovered;     // Has the player seen this Space before?
};

#endif // SPACE_H
