
#ifndef LOVE_DATA_WRAP_NOISEDATA_H
#define LOVE_DATA_WRAP_NOISEDATA_H

// LOVE
#include "NoiseData.h"
#include "common/runtime.h"

namespace love
{
namespace data
{

NoiseData *luax_checknoisedata(lua_State *L, int idx);
extern "C" int luaopen_noisedata(lua_State *L);

} // math
} // love

#endif // LOVE_DATA_WRAP_NOISEDATA_H
