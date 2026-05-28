/* Colors.h
 * This file contains color definitions, to avoid having to define them all
 * inline.
 */

#ifndef HEX_COLORS_H
#define HEX_COLORS_H

#include <SDL2/SDL.h>

namespace Colors {
static const SDL_Color gray = {128, 128, 128, 255};
static const SDL_Color darkGray = {64, 64, 64, 255};
static const SDL_Color white = {255, 255, 255, 255};
static const SDL_Color red = {255, 0, 0, 255};
} // namespace Colors
#endif //HEX_COLORS_H
