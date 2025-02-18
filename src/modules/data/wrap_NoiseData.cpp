
#include "wrap_NoiseData.h"

namespace love
{
namespace data
{

NoiseData *luax_checknoisedata(lua_State *L, int idx)
{
	return luax_checktype<NoiseData>(L, idx, NoiseData::type);
}

int w_NoiseData_clear(lua_State *L)
{
	NoiseData *n = luax_checknoisedata(L, 1);
	n->clear();
	return 0;
}

static const luaL_Reg functions[] =
{
	{ "clear", w_NoiseData_clear },
	{ 0, 0 }
};

extern "C" int luaopen_noisedata(lua_State *L)
{
	return luax_register_type(L, &NoiseData::type, functions, nullptr);
}

} // data
} // love
