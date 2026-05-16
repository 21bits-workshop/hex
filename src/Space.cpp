#include "Space.h"

Space::Space()
    : characterColor({0, 0, 0, 255}), displayCharacter(' '), traversable(true),
      blocksLOSValue(false), visible(false), discovered(false) {}

Space::Space(SDL_Color color, char character, bool traversable, bool blocksLOS,
             bool visible, bool discovered)
    : characterColor(color), displayCharacter(character),
      traversable(traversable), blocksLOSValue(blocksLOS), visible(visible),
      discovered(discovered) {}

void Space::setCharacterColor(SDL_Color color) { characterColor = color; }
SDL_Color Space::getCharacterColor() const { return characterColor; }

void Space::setDisplayCharacter(char character) {
  displayCharacter = character;
}
char Space::getDisplayCharacter() const { return displayCharacter; }

void Space::setTraversable(bool traversable) {
  this->traversable = traversable;
}
bool Space::isTraversable() const { return traversable; }

void Space::setBlocksLOS(bool blocksLOS) { this->blocksLOSValue = blocksLOS; }
bool Space::blocksLOS() const { return blocksLOSValue; }

void Space::setVisible(bool visible) { this->visible = visible; }
bool Space::isVisible() const { return visible; }

void Space::setDiscovered(bool discovered) { this->discovered = discovered; }
bool Space::isDiscovered() const { return discovered; }
