#pragma bank 255

#include <gbdk/platform.h>

#include "screen.h"
#include "bankdata.h"

#include "common_tiles.h"

void misc_assets_init() BANKED {
#ifdef NINTENDO
    set_banked_data(TO_TILE_ADDRESS(_VRAM8000, (256 - common_tiles_TILE_COUNT)), common_tiles_tiles, (common_tiles_TILE_COUNT << 4), BANK(common_tiles));
#endif
}
