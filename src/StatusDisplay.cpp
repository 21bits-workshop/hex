#include "StatusDisplay.h"
#include "Constants.h"
#include "Game.h"
#include "Map.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>

StatusDisplay::StatusDisplay(TTF_Font *font)
    : width(Constants::TILE_SIZE * Constants::MAP_WIDTH),
      height(Constants::TILE_SIZE * 6), tileSize(Constants::TILE_SIZE),
      font(font) {}

void StatusDisplay::updateDisplayTexture(SDL_Renderer *renderer, int tileSize,
                                         std::shared_ptr<Player> player,
                                         Game *game) {
  if (m_statusDisplayTexture) {
    SDL_DestroyTexture(m_statusDisplayTexture);
    m_statusDisplayTexture = nullptr;
  }
  SDL_Surface *displaySurface =
      SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

  SDL_Surface *nameSurface =
      TTF_RenderText_Blended(font, player->getName(), {255, 255, 255, 255});
  SDL_Rect nameDestRect = {0, 0, 1, 1};
  SDL_BlitSurface(nameSurface, NULL, displaySurface, &nameDestRect);

  std::string classLevelString = "Level 0 Freelancer";
  SDL_Surface *classLevelSurface = TTF_RenderText_Blended(
      font, classLevelString.c_str(), {255, 255, 255, 255});
  SDL_Rect classLevelDestRect = {
      Constants::TILE_SIZE * static_cast<int>(std::strlen(player->getName())) +
          Constants::TILE_SIZE * 3,
      0, 1, 1};
  SDL_BlitSurface(classLevelSurface, NULL, displaySurface, &classLevelDestRect);

  // TODO: Add Current HP to Player and have that reflected here.
  std::string hpString = "HP: 10/" + std::to_string(player->getMaxHP());
  SDL_Surface *hpSurface =
      TTF_RenderText_Blended(font, hpString.c_str(), {255, 255, 255, 255});
  SDL_Rect hpDestRect = {0, Constants::TILE_SIZE, 1, 1};
  SDL_BlitSurface(hpSurface, NULL, displaySurface, &hpDestRect);

  std::string physicalDefenseString =
      "Phy.Defense: " + std::to_string(player->getPhysicalDefense()) + "[" +
      std::to_string(player->getPhysicalProtection()) + "]";
  SDL_Surface *physicalDefenseSurface = TTF_RenderText_Blended(
      font, physicalDefenseString.c_str(), {255, 255, 255, 255});
  SDL_Rect physicalDefenseDestRect = {0, Constants::TILE_SIZE * 2, 1, 1};
  SDL_BlitSurface(physicalDefenseSurface, NULL, displaySurface,
                  &physicalDefenseDestRect);

  std::string psionicDefenseString =
      "Psi.Defense: " + std::to_string(player->getPsionicDefense());
  SDL_Surface *psionicDefenseSurface = TTF_RenderText_Blended(
      font, psionicDefenseString.c_str(), {255, 255, 255, 255});
  SDL_Rect psionicDefenseDestRect = {
      (physicalDefenseDestRect.x) +
          (Constants::TILE_SIZE *
           static_cast<int>(physicalDefenseString.length())) +
          (Constants::TILE_SIZE * 2),
      Constants::TILE_SIZE * 2, 1, 1};
  SDL_BlitSurface(psionicDefenseSurface, NULL, displaySurface,
                  &psionicDefenseDestRect);

  std::string attributesString =
      "ST: " + std::to_string(player->getStrength()) +
      " IN: " + std::to_string(player->getIntelligence()) +
      " WI: " + std::to_string(player->getWillpower()) +
      " AG: " + std::to_string(player->getAgility()) +
      " CH: " + std::to_string(player->getCharisma()) +
      " CO: " + std::to_string(player->getConstitution());
  SDL_Surface *attributesSurface = TTF_RenderText_Blended(
      font, attributesString.c_str(), {255, 255, 255, 255});
  SDL_Rect attributesDestRect = {
      classLevelDestRect.x +
          static_cast<int>(classLevelString.length()) * Constants::TILE_SIZE +
          Constants::TILE_SIZE * 2,
      0, 1, 1};
  SDL_BlitSurface(attributesSurface, NULL, displaySurface, &attributesDestRect);

  std::string cyberDefenseString =
      "Cyb.Defense " + std::to_string(player->getCyberDefense());
  SDL_Surface *cyberDefenseSurface = TTF_RenderText_Blended(
      font, cyberDefenseString.c_str(), {255, 255, 255, 255});
  SDL_Rect cyberDefenseDestRect = {
      (psionicDefenseDestRect.x) +
          (Constants::TILE_SIZE *
           static_cast<int>(psionicDefenseString.length())) +
          (Constants::TILE_SIZE * 2),
      Constants::TILE_SIZE * 2, 1, 1};
  SDL_BlitSurface(cyberDefenseSurface, NULL, displaySurface,
                  &cyberDefenseDestRect);

  std::string integrityString =
      "Integrity: 10/" + std::to_string(player->getIntegrity());
  SDL_Surface *integritySurface = TTF_RenderText_Blended(
      font, integrityString.c_str(), {255, 255, 255, 255});
  SDL_Rect integrityDestRect = {
      (hpDestRect.x) +
          (Constants::TILE_SIZE * static_cast<int>(hpString.length())) +
          (Constants::TILE_SIZE * 2),
      Constants::TILE_SIZE, 1, 1};
  SDL_BlitSurface(integritySurface, NULL, displaySurface, &integrityDestRect);

  // TODO: Add current SP to Player and have that reflected here.
  std::string spString = "SP: 10/" + std::to_string(player->getMaxSP());
  SDL_Surface *spSurface =
      TTF_RenderText_Blended(font, spString.c_str(), {255, 255, 255, 255});
  SDL_Rect spDestRect = {
      (integrityDestRect.x) +
          (Constants::TILE_SIZE * static_cast<int>(integrityString.length())) +
          (Constants::TILE_SIZE * 2),
      Constants::TILE_SIZE, 1, 1};
  SDL_BlitSurface(spSurface, NULL, displaySurface, &spDestRect);

  // TODO: Add a Current Flame value to Player and have that reflected here
  SDL_Surface *flameSurface =
      TTF_RenderText_Blended(font, "Flame: Strong", {255, 255, 255, 255});
  SDL_Rect flameDestRect = {
      (spDestRect.x) +
          (Constants::TILE_SIZE * static_cast<int>(spString.length())) +
          (Constants::TILE_SIZE * 2),
      Constants::TILE_SIZE, 1, 1};
  SDL_BlitSurface(flameSurface, NULL, displaySurface, &flameDestRect);

  std::string worldTypeString = "";
  if (&game->getCurrentMap() == &game->getOverworld()) {
    worldTypeString = "Overworld";
  } else if (&game->getCurrentMap() == &game->getReality()) {
    worldTypeString = "Reality";
  } else if (&game->getCurrentMap() == &game->getCyberspace()) {
    worldTypeString = "Cyberspace";
  } else {
    worldTypeString = "World Error!";
  }

  SDL_Surface *worldTypeSurface = TTF_RenderText_Blended(
      font, worldTypeString.c_str(), {255, 255, 255, 255});
  SDL_Rect worldTypeDestRect = {displaySurface->w / 2, displaySurface->h / 6, 1,
                                1};
  SDL_BlitSurface(worldTypeSurface, NULL, displaySurface, &worldTypeDestRect);

  SDL_Texture *displayTexture =
      SDL_CreateTextureFromSurface(renderer, displaySurface);
  int w, h;
  SDL_QueryTexture(displayTexture, NULL, NULL, &w, &h);
  SDL_Rect destRect = {Constants::TILE_SIZE,
                       (Constants::TILE_SIZE * 8 +
                        Constants::TILE_SIZE * Constants::MAP_HEIGHT +
                        Constants::TILE_SIZE),
                       w, h};
  SDL_RenderCopy(renderer, displayTexture, NULL, &destRect);
  SDL_DestroyTexture(displayTexture);

  SDL_FreeSurface(nameSurface);
  SDL_FreeSurface(classLevelSurface);
  SDL_FreeSurface(hpSurface);
  SDL_FreeSurface(physicalDefenseSurface);
  SDL_FreeSurface(flameSurface);
  SDL_FreeSurface(psionicDefenseSurface);
  SDL_FreeSurface(attributesSurface);
  SDL_FreeSurface(cyberDefenseSurface);
  SDL_FreeSurface(worldTypeSurface);
  SDL_FreeSurface(displaySurface);
}
