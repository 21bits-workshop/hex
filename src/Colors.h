/* Colors.h
 * This file contains color definitions, to avoid having to define them all
 * inline.
 */

#ifndef HEX_COLORS_H
#define HEX_COLORS_H

#include <SDL2/SDL.h>

namespace Colors {
// Test colors
static const SDL_Color gray = {128, 128, 128, 255};
static const SDL_Color darkGray = {64, 64, 64, 255};
static const SDL_Color white = {255, 255, 255, 255};
static const SDL_Color red = {255, 0, 0, 255};

// Catppuccin mocha
static const SDL_Color mocha_rosewater = {245, 244, 220, 255};
static const SDL_Color mocha_flamingo = {242, 205, 205, 255};
static const SDL_Color mocha_pink = {245, 194, 231, 255};
static const SDL_Color mocha_mauve = {203, 166, 247, 255};
static const SDL_Color mocha_red = {243, 139, 168, 255};
static const SDL_Color mocha_maroon = {235, 160, 172, 255};
static const SDL_Color mocha_peach = {250,179,135,255};
static const SDL_Color mocha_yellow = {249,226,175,255};
static const SDL_Color mocha_green = {167,227,161,256};
static const SDL_Color mocha_teal = {148,226,213,255};
static const SDL_Color mocha_sky = {137,220,235,255};
static const SDL_Color mocha_saphhire = {116,199,236,255};
static const SDL_Color mocha_blue = {137,180,250,255};
} // namespace Colors
#endif //HEX_COLORS_H
