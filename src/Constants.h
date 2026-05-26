/* Constants.h
 * This file contains global static constants that will be used
 * throughout the codebase, to avoid the rampant use of magic numbers.
 */

#ifndef HEX_CONST_H
#define HEX_CONST_H
#include <string>

namespace Constants {
static const int MAP_WIDTH = 132;
static const int MAP_HEIGHT = 64;
static const int TILE_SIZE = 14;
//TODO: Create a local font and use that, instead of assuming the user is on my home computer :p
static const char *FONT_PATH = "/usr/share/fonts/Adwaita/AdwaitaMono-Bold.ttf";

static const int SIGHT_RADIUS =
    6; // This will become variable and stored in Player later.
} // namespace Constants

#endif // HEX_CONST_H
