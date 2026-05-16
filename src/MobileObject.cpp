#include "MobileObject.h"

MobileObject::MobileObject(int x, int y, char displayCharacter,
                           SDL_Color fgColor)
    : Entity(x, y, displayCharacter, fgColor) {}

void MobileObject::move(int dx, int dy, int mapWidth, int mapHeight) {
  int newX = getX() + dx;
  int newY = getY() + dy;

  if (newX >= 0 && newX < mapWidth && newY >= 0 && newY < mapHeight) {
    setX(newX);
    setY(newY);
  }
}

// ************* Welcome to getter/setter hell *************
int MobileObject::getStrength() const { return strength; }
void MobileObject::setStrength(int value) { strength = value; }

int MobileObject::getIntelligence() const { return intelligence; }
void MobileObject::setIntelligence(int value) { intelligence = value; }

int MobileObject::getWillpower() const { return willpower; }
void MobileObject::setWillpower(int value) { willpower = value; }

int MobileObject::getAgility() const { return agility; }
void MobileObject::setAgility(int value) { agility = value; }

int MobileObject::getCharisma() const { return charisma; }
void MobileObject::setCharisma(int value) { charisma = value; }

int MobileObject::getConstitution() const { return constitution; }
void MobileObject::setConstitution(int value) { constitution = value; }

int MobileObject::getSpeed() const { return speed; }
void MobileObject::setSpeed(int value) { speed = value; }
// *********** Interesting methods below here **************

void MobileObject::update() { controller.update(); }
