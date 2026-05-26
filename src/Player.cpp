#include "Player.h"
#include "Colors.h"
#include "Game.h"
#include "PlayerController.h"
#include <cstring>
#include <string>
#include <unordered_map>

Player::Player(int overworldX, int overworldY, int realityX, int realityY,
               int cyberspaceX, int cyberspaceY, char displayCharacter,
               char *name, Game *game)
    : MobileObject(2, 2, displayCharacter, Colors::white,
                   new PlayerController(game)),
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

int Player::getResourceTotal(std::string id) const {
  return resourceTotals.at(id);
}

int Player::getRealityStat(std::string id) const { return realityStats.at(id); }

int Player::getCyberspaceStat(std::string id) const {
  return cyberspaceStats.at(id);
}

int Player::getSkill(std::string id) const { return skills.at(id); }

char *Player::getName() const { return name; }

PlayerController *Player::getPlayerController() {
  return static_cast<PlayerController *>(this->getController());
}
// ************ Interesting methods below ******************

// TODO: Actually work out how stats should be derived.
void Player::recalculateStats() {
  realityStats["meleeAttack"] = 10;
  realityStats["psionicAttack"] = 10;
  realityStats["rangedAttack"] = 10;
  realityStats["accuracy"] = 10;
  realityStats["physicalDefense"] = 10;
  realityStats["physicalProtection"] = 10;
  realityStats["psionicDefense"] = 10;
  realityStats["bounceDamageProtection"] = 10;
  realityStats["avatarDeathProtection"] = 10;
  realityStats["maxHP"] = 10;
  realityStats["flameRecovery"] = 10;
  realityStats["carryingCapacity"] = 10;

  cyberspaceStats["cyberAttack"] = 10;
  cyberspaceStats["bruteForceAttack"] = 10;
  cyberspaceStats["precision"] = 10;
  cyberspaceStats["spellPower"] = 10;
  cyberspaceStats["cyberDefense"] = 10;
  cyberspaceStats["bounceResistance"] = 10;
  cyberspaceStats["maxIntegrity"] = 10;
  cyberspaceStats["maxSP"] = 10;
  cyberspaceStats["memory"] = 10;

  resourceTotals["currentHP"] = realityStats["maxHP"];
  resourceTotals["currentSP"] = cyberspaceStats["maxSP"];
  resourceTotals["flame"] = 4;
  resourceTotals["currentIntegrity"] = cyberspaceStats["maxIntegrity"];

  skills["hacking"] = 10;
  skills["bartering"] = 10;
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
