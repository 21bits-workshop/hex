/* MobileObject.h
 *
 * MobileObjects are Entities that are capable of moving
 * themselves around the map. They each have an ObjectController,
 * an object which will contain the logic the MobileObject is to execute
 * on its game turn.
 */

#ifndef MOBILE_OBJECT_H
#define MOBILE_OBJECT_H

#include "Entity.h"
#include "ObjectController.h"

class MobileObject : public Entity {
public:
  MobileObject(int x, int y, char displayCharacter, SDL_Color fgColor);

  void move(int dx, int dy, int mapWidth, int mapHeight);

  int getStrength() const;
  void setStrength(int value);

  int getIntelligence() const;
  void setIntelligence(int value);

  int getWillpower() const;
  void setWillpower(int value);

  int getAgility() const;
  void setAgility(int value);

  int getCharisma() const;
  void setCharisma(int value);

  int getConstitution() const;
  void setConstitution(int value);

  int getSpeed() const;
  void setSpeed(int value);

  ObjectController *getController();
  /**************************************************************************
   * For now, update() will simply call the ObjectController's
   * update method.
   *************************************************************************/
  void update();

private:
  ObjectController controller;

  // Main Attributes
  int strength, intelligence, willpower, agility, charisma, constitution;

  // Speed
  int speed;
};

#endif // MOBILE_OBJECT_H
