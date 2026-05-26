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
#include "PlayerController.h"
#include <string>
#include <unordered_map>

class Player : public MobileObject {
public:
  Player(int overworldX, int overworldY, int realityX, int realityY,
         int cyberspaceX, int cyberspaceY, char displayCharacter, char *name,
         Game *game);

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

  int getResourceTotal(std::string id) const;
  int getRealityStat(std::string id) const;
  int getCyberspaceStat(std::string id) const;
  int getSkill(std::string id) const;

  char *getName() const;

  PlayerController *getPlayerController();

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

  std::unordered_map<std::string, int> resourceTotals;
  std::unordered_map<std::string, int> realityStats;
  std::unordered_map<std::string, int> cyberspaceStats;
  std::unordered_map<std::string, int> skills;
};

#endif // PLAYER_H
