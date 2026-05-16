/* Entity.h 
 * Entity is the parent class of all non-Space game objects that have a
 * location on-map and a character to represent them.
 */

#include <SDL2/SDL.h>

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    Entity(int x, int y, char displayCharacter, SDL_Color fgColor);
    virtual ~Entity() = default;

    int getX() const;
    int getY() const;
    char getDisplayCharacter() const;
    SDL_Color getFgColor() const;

    void setX(int x);
    void setY(int y);
    void setDisplayCharacter(char c);
    void setFgColor(SDL_Color color);

private:
    int x;
    int y;
    char displayCharacter;
    SDL_Color fgColor;
};

#endif // ENTITY_H
