#include "Player.h"
#include <cstring>

Player::Player(int overworldX, int overworldY, int realityX, int realityY,
               int cyberspaceX, int cyberspaceY, char displayCharacter,
               char *name)
    : MobileObject(2, 2, displayCharacter, {255, 255, 255, 255} /*White*/),
      overworldX(overworldX), overworldY(overworldY), realityX(realityX),
      realityY(realityY), cyberspaceX(cyberspaceX), cyberspaceY(cyberspaceY),
      name(name) {
  syncActiveCoordinates("overworld"); // Game begins on the Overworld map.
  recalculateStats();                 // Otherwise all stats will be empty.
}

// ************* Welcome to getter/setter hell *************
int Player::getOverworldX() const { return overworldX; }
void Player::setOverworldX(int x) { overworldX = x; }
int Player::getOverworldY() const { return overworldY; }
void Player::setOverworldY(int y) { overworldY = y; }

int Player::getRealityX() const { return realityX; }
void Player::setRealityX(int x) { realityX = x; }
int Player::getRealityY() const { return realityY; }
void Player::setRealityY(int y) { realityY = y; }

int Player::getCyberspaceX() const { return cyberspaceX; }
void Player::setCyberspaceX(int x) { cyberspaceX = x; }
int Player::getCyberspaceY() const { return cyberspaceY; }
void Player::setCyberspaceY(int y) { cyberspaceY = y; }

int Player::getMeleeAttack() const { return meleeAttack; }
int Player::getPsionicAttack() const { return psionicAttack; }
int Player::getRangedAttack() const { return rangedAttack; }
int Player::getAccuracy() const { return accuracy; }
int Player::getPhysicalDefense() const { return physicalDefense; }
int Player::getPhysicalProtection() const { return physicalProtection; }
int Player::getPsionicDefense() const { return psionicDefense; }
int Player::getBounceDamageProtection() const { return bounceDamageProtection; }
int Player::getAvatarDeathProtection() const { return avatarDeathProtection; }
int Player::getHacking() const { return hacking; }
int Player::getBartering() const { return bartering; }
int Player::getMaxHP() const { return maxHP; }
int Player::getFlameRecovery() const { return flameRecovery; }
int Player::getCarryingCapacity() const { return carryingCapacity; }

int Player::getCyberAttack() const { return cyberAttack; }
int Player::getBruteForceAttack() const { return bruteForceAttack; }
int Player::getPrecision() const { return precision; }
int Player::getSpellPower() const { return spellPower; }
int Player::getCyberDefense() const { return cyberDefense; }
int Player::getBounceResistance() const { return bounceResistance; }
int Player::getIntegrity() const { return integrity; }
int Player::getMaxSP() const { return maxSP; }
int Player::getMemory() const { return memory; }

char *Player::getName() const { return name; }

PlayerController *Player::getPlayerController() {
  return static_cast<PlayerController *>(this->getController());
}
// ************ Interesting methods below ******************

// TODO: Actually work out how stats should be derived.
void Player::recalculateStats() {
  meleeAttack = 10;
  psionicAttack = 10;
  rangedAttack = 10;
  accuracy = 10;
  physicalDefense = 10;
  physicalProtection = 10;
  psionicDefense = 10;
  bounceDamageProtection = 10;
  avatarDeathProtection = 10;
  hacking = 10;
  bartering = 10;
  maxHP = 10;
  flameRecovery = 10;
  carryingCapacity = 10;

  cyberAttack = 10;
  bruteForceAttack = 10;
  precision = 10;
  spellPower = 10;
  cyberDefense = 10;
  bounceResistance = 10;
  integrity = 10;
  maxSP = 10;
  memory = 10;
}

void Player::syncActiveCoordinates(const char *worldType) {
  if (std::strcmp(worldType, "overworld") == 0) {
    setX(overworldX);
    setY(overworldY);
  } else if (std::strcmp(worldType, "reality") == 0) {
    setX(realityX);
    setY(realityY);
  } else if (std::strcmp(worldType, "cyberspace") == 0) {
    setX(cyberspaceX);
    setY(cyberspaceY);
  }
}
