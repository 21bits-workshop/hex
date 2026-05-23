/* Map.h
 * The map class represents the game world(s) as an array of Space objects,
 * each of which stores a single map square's display and gameplay parameters.
 */

#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "MobileObject.h"
#include "Space.h"
#include <memory>
#include <vector>

class Map {
public:
  Map(int width, int height);

  // TODO: Add different kinds of map generation (Random walk, erosion, etc.)
  static Map createWallMap(int width, int height);
  static Map generateRoomAndHallwayMap(int width, int height, int numRooms,
                                       int minRoomSize, int maxRoomSize);

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  bool isWithinBounds(int x, int y) const;

  // We need both a const and a mutable version here because of the
  // const Map& paramater in WorldDisplay.draw. TODO: Look at cleaning this up.
  Space &getSpace(int x, int y);
  const Space &getSpace(int x, int y) const;
  Space &getSpaceLinear(int idx);

  void addEntity(std::shared_ptr<Entity> entity);
  const std::vector<std::shared_ptr<Entity>> &getEntities() const {
    return entities;
  }

  int getPlayerStartX() const { return playerStartX; }
  int getPlayerStartY() const { return playerStartY; }

private:
  int width;
  int height;
  int playerStartX;
  int playerStartY;
  std::vector<Space> spaces;
  std::vector<std::shared_ptr<Entity>> entities;
};

#endif // MAP_H
