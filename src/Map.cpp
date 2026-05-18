#include "Map.h"
#include <algorithm>
#include <random>
#include <vector>

struct Rect {
  int x, y, w, h;
  bool intersects(const Rect &other) {
    return !(x + w < other.x || x > other.x + other.w || y + h < other.y ||
             y > other.y + other.h);
  }
  int centerX() const { return x + w / 2; }
  int centerY() const { return y + h / 2; }
};

Map::Map(int width, int height)
    : width(width), height(height), playerStartX(0), playerStartY(0) {
  spaces.resize(width * height);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      spaces[y * width + x] = Space();
    }
  }
}

void Map::addEntity(std::shared_ptr<Entity> entity) {
  entities.push_back(std::move(entity));
}

bool Map::isWithinBounds(int x, int y) const {
  return x >= 0 && x < width && y >= 0 && y < height;
}

Space &Map::getSpace(int x, int y) { return spaces[y * width + x]; }

const Space &Map::getSpace(int x, int y) const { return spaces[y * width + x]; }

Map Map::createWallMap(int width, int height) {
  Map map(width, height);
  map.playerStartX = 3;
  map.playerStartY = 3;
  SDL_Color gray = {128, 128, 128, 255};
  SDL_Color darkGray = {64, 64, 64, 255};
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      Space &s = map.getSpace(x, y);
      s.setCharacterColor(gray);
      s.setDisplayCharacter('#');
      s.setTraversable(false);
      s.setBlocksLOS(true);
      s.setVisible(true);
      s.setDiscovered(false);
    }
  }
  for (int y = 1; y < height - 1; ++y) {
    for (int x = 1; x < width - 1; ++x) {
      Space &s = map.getSpace(x, y);
      s.setCharacterColor(darkGray);
      s.setDisplayCharacter('.');
      s.setTraversable(true);
      s.setBlocksLOS(false);
      s.setVisible(true);
      s.setDiscovered(true);
    }
  }
  return map;
}

Map Map::generateRoomAndHallwayMap(int width, int height, int numRooms,
                                   int minRoomSize, int maxRoomSize) {
  Map map(width, height);
  SDL_Color wallColor = {128, 128, 128, 255};
  SDL_Color floorColor = {64, 64, 64, 255};

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      Space &s = map.getSpace(x, y);
      s.setCharacterColor(wallColor);
      s.setDisplayCharacter('#');
      s.setTraversable(false);
      s.setBlocksLOS(true);
      s.setVisible(false);
      s.setDiscovered(false);
    }
  }

  std::vector<Rect> rooms;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> disW(minRoomSize, maxRoomSize);
  std::uniform_int_distribution<> disH(minRoomSize, maxRoomSize);

  for (int i = 0; i < numRooms; ++i) {
    int w = disW(gen);
    int h = disH(gen);
    if (w >= width - 2 || h >= height - 2)
      continue;

    int x = std::uniform_int_distribution<>(1, width - w - 1)(gen);
    int y = std::uniform_int_distribution<>(1, height - h - 1)(gen);
    Rect newRoom = {x, y, w, h};

    bool overlap = false;
    for (const auto &room : rooms) {
      if (newRoom.intersects(room)) {
        overlap = true;
        break;
      }
    }

    if (!overlap) {
      if (!rooms.empty()) {
        map.playerStartX = rooms.back().centerX();
        map.playerStartY = rooms.back().centerY();
      }
      if (!rooms.empty()) {
        // TODO: Change this to target random points within the rough center of
        // a room.
        const Rect &prevRoom = rooms.back();
        int startX = prevRoom.centerX();
        int startY = prevRoom.centerY();
        int endX = newRoom.centerX();
        int endY = newRoom.centerY();

        // Horizontal section of hallway
        int minX = std::min(startX, endX);
        int maxX = std::max(startX, endX);
        for (int curX = minX; curX <= maxX; ++curX) {
          Space &s = map.getSpace(curX, startY);
          s.setCharacterColor(floorColor);
          s.setDisplayCharacter('.');
          s.setTraversable(true);
          s.setBlocksLOS(false);
        }

        // Vertical section of hallway
        int minY = std::min(startY, endY);
        int maxY = std::max(startY, endY);
        for (int curY = minY; curY <= maxY; ++curY) {
          Space &s = map.getSpace(endX, curY);
          s.setCharacterColor(floorColor);
          s.setDisplayCharacter('.');
          s.setTraversable(true);
          s.setBlocksLOS(false);
        }
      }

      rooms.push_back(newRoom);

      // Carve the room
      for (int ry = y; ry < y + h; ++ry) {
        for (int rx = x; rx < x + w; ++rx) {
          Space &s = map.getSpace(rx, ry);
          s.setCharacterColor(floorColor);
          s.setDisplayCharacter('.');
          s.setTraversable(true);
          s.setBlocksLOS(false);
        }
      }
    }
  }
  return map;
}
