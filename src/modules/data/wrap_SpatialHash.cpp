
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
	float x = luax_checkfloat(L, 2);
	float y = luax_checkfloat(L, 3);
	int id = s->add(x, y);
	if (id < 0)
		return luaL_error(L, "SpatialHash add element error");

	lua_pushnumber(L, id);
	return 1;
}

int w_SpatialHash_set(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	int id = luax_checkint(L, 2);
	float x = luax_checkfloat(L, 3);
	float y = luax_checkfloat(L, 4);
	s->set(id, x, y);
	return 0;
}

int w_SpatialHash_get(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	int id = (int) luaL_checkinteger(L, 2);
	float x = 0, y = 0;
	if (!s->get(id, x, y))
	{
		lua_pushnil(L);
		return 1;
	}

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

int w_SpatialHash_query(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	s->query(0.0f, 0.0f, 0.0f);
	return 0;
}

int w_SpatialHash_clear(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	s->clear();
	return 0;
}

int w_SpatialHash_process(lua_State *L)
{
	SpatialHash *s = luax_checkspatialhash(L, 1);
	s->process();
	return 0;
}

int w_SpatialHash_getData(lua_State *L)
{
    SpatialHash *s = luax_checkspatialhash(L, 1);
    love::data::ByteData *data = const_cast<love::data::ByteData *>(&s->getData());
    luax_pushtype(L, love::data::ByteData::type, data);
    return 1;
}

static const luaL_Reg functions[] =
{
	{ "add", w_SpatialHash_add },
	{ "set", w_SpatialHash_set },
	{ "get", w_SpatialHash_get },
	{ "clear", w_SpatialHash_clear },
	{ "query", w_SpatialHash_query },
	{ "process", w_SpatialHash_process },
	{ "getData", w_SpatialHash_getData },
	{ 0, 0 }
};

extern "C" int luaopen_spatialhash(lua_State *L)
{
	return luax_register_type(L, &SpatialHash::type, functions, nullptr);
}

} // data
} // love
