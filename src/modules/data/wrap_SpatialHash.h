
#ifndef LOVE_DATA_WRAP_SPATIALHASH_H
#define LOVE_DATA_WRAP_SPATIALHASH_H

// LOVE
#include "SpatialHash.h"
#include "common/runtime.h"

namespace love
{
namespace data
{

SpatialHash *luax_checkspatialhash(lua_State *L, int idx);
extern "C" int luaopen_spatialhash(lua_State *L);

} // math
} // love

#endif