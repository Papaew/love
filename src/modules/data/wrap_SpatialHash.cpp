
#include "wrap_SpatialHash.h"

namespace love
{
namespace data
{

SpatialHash *luax_checkspatialhash(lua_State *L, int idx)
{
	return luax_checktype<SpatialHash>(L, idx, SpatialHash::type);
}

int w_SpatialHash_add(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	s->add(0, 0.0f, 0.0f);
	return 0;
}

int w_SpatialHash_query(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	s->query(0.0f, 0.0f, 0.0f);
	return 0;
}

int w_SpatialHash_reset(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	s->reset();
	return 0;
}

static const luaL_Reg functions[] =
{
	{ "add", w_SpatialHash_add },
	{ "query", w_SpatialHash_query },
	{ "reset", w_SpatialHash_reset },
	{ 0, 0 }
};

extern "C" int luaopen_spatialhash(lua_State *L)
{
	return luax_register_type(L, &SpatialHash::type, functions, nullptr);
}

} // data
} // love
