/* Player.h
 * The Player object is a special case of a MobileObject with three
 * sets of coordinates - one each for its position on the overworld, the reality
 * map, and the cyberspace map. Its ObjectController contains the code for
 * processing user input - so the player can only interact with the game
 * when it is their turn.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "MobileObject.h"

class Player : public MobileObject {
public:
  Player(int overworldX, int overworldY, int realityX, int realityY,
         int cyberspaceX, int cyberspaceY, char displayCharacter, char *name);

  int getOverworldX() const;
  void setOverworldX(int x);
  int getOverworldY() const;
  void setOverworldY(int y);

  int getRealityX() const;
  void setRealityX(int x);
  int getRealityY() const;
  void setRealityY(int y);

  int getCyberspaceX() const;
  void setCyberspaceX(int x);
  int getCyberspaceY() const;
  void setCyberspaceY(int y);

  int getMeleeAttack() const;
  int getPsionicAttack() const;
  int getRangedAttack() const;
  int getAccuracy() const;
  int getPhysicalDefense() const;
  int getPhysicalProtection() const;
  int getPsionicDefense() const;
  int getBounceDamageProtection() const;
  int getAvatarDeathProtection() const;
  int getHacking() const;
  int getBartering() const;
  int getMaxHP() const;
  int getFlameRecovery() const;
  int getCarryingCapacity() const;

  int getCyberAttack() const;
  int getBruteForceAttack() const;
  int getPrecision() const;
  int getSpellPower() const;
  int getCyberDefense() const;
  int getBounceResistance() const;
  int getIntegrity() const;
  int getMaxSP() const;
  int getMemory() const;

  char *getName() const;

  void recalculateStats();

  /**************************************************************************
   * syncActiveCoordinates is called each time the active map is changed,
   * and moves the player's coordinates for the current map into the
   * "base" coordinates provided by Entity, which are actually used to
   * draw the character.
   *************************************************************************/
  void syncActiveCoordinates(const char *worldType);

private:
  // Map Coordinates
  int overworldX, overworldY;
  int realityX, realityY;
  int cyberspaceX, cyberspaceY;

  // Note that the Main Attributes and speed are properties of MobileObject,
  // since every moving entity will need a speed stat and the attributes to
  // calculate it with.

  // Personal Details
  char *name;

  // Reality Offensive Derived Stats
  int meleeAttack, psionicAttack, rangedAttack, accuracy;

  // Reality Defensive Derived Stats
  int physicalDefense, physicalProtection, psionicDefense,
      bounceDamageProtection, avatarDeathProtection;

  // Reality World Derived Skills
  int hacking, bartering;

  // Reality Resource Derived Stats
  int maxHP, flameRecovery, carryingCapacity;

  // Cyberspace Offensive Derived Stats
  int cyberAttack, bruteForceAttack, precision, spellPower;

  // Cyberspace Defensive Derived Stats
  int cyberDefense, bounceResistance;

  // Cyberspace Resource Derived Stats
  int integrity, maxSP, memory;
};

#endif // PLAYER_H
