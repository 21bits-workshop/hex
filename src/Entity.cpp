#include "Entity.h"
#include <SDL2/SDL_ttf.h>

Entity::Entity(int x, int y, char displayCharacter, SDL_Color fgColor)
    : x(x), y(y), displayCharacter(displayCharacter), fgColor(fgColor) {}

// Getters & Setters ==============================
int Entity::getX() const { return x; }
int Entity::getY() const { return y; }
char Entity::getDisplayCharacter() const { return displayCharacter; }
SDL_Color Entity::getFgColor() const { return fgColor; }

void Entity::setX(int newX) { x = newX; }
void Entity::setY(int newY) { y = newY; }
void Entity::setDisplayCharacter(char c) { displayCharacter = c; }
void Entity::setFgColor(SDL_Color color) { fgColor = color; }
// ================================================