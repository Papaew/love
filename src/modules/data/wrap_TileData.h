
#ifndef LOVE_DATA_WRAP_TILEDATA_H
#define LOVE_DATA_WRAP_TILEDATA_H

// LOVE
#include "TileData.h"
#include "common/runtime.h"

namespace love
{
namespace data
{

TileData *luax_checktiledata(lua_State *L, int idx);
extern "C" int luaopen_tiledata(lua_State *L);

} // math
} // love

#endif // LOVE_DATA_WRAP_TILEDATA_H
