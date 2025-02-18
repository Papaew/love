
#include "wrap_TileData.h"

namespace love
{
namespace data
{

TileData *luax_checktiledata(lua_State *L, int idx)
{
	return luax_checktype<TileData>(L, idx, TileData::type);
}

int w_TileData_clear(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	t->clear();
	return 0;
}

int w_TileData_generate(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	t->generate();
	return 0;
}

int w_TileData_setTileValue(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	int ix = (int) luaL_checkinteger(L, 2);
	int iy = (int) luaL_checkinteger(L, 3);
	int value = (int) luaL_checkinteger(L, 4);
	t->setTileValue(ix, iy, value);
	return 0;
}

int w_TileData_getWidth(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	lua_pushinteger(L, (lua_Integer) t->getWidth());
	return 1;
}

int w_TileData_getVirtualWidth(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	lua_pushinteger(L, (lua_Integer) t->getVirtualWidth());
	return 1;
}

int w_TileData_getSurfaceLevel(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	lua_pushnumber(L, (lua_Number) t->getSurfaceLevel());
	return 1;
}

int w_TileData_getTileValue(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	int ix = (int) luaL_checkinteger(L, 2);
	int iy = (int) luaL_checkinteger(L, 3);
	lua_pushnumber(L, (lua_Number) t->getTileValue(ix, iy));
	return 1;
}

int w_TileData_getData(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	love::data::ByteData *data = const_cast<love::data::ByteData *>(&t->getData());
	luax_pushtype(L, love::data::ByteData::type, data);
	return 1;
}

static const luaL_Reg functions[] =
{
	{ "clear", w_TileData_clear },
	{ "generate", w_TileData_generate },

	{ "setTileValue", w_TileData_setTileValue },

	{ "getWidth", w_TileData_getWidth },
	{ "getVirtualWidth", w_TileData_getVirtualWidth },
	{ "getTileValue", w_TileData_getTileValue },
	{ "getSurfaceLevel", w_TileData_getSurfaceLevel },
	{ "getData", w_TileData_getData },
	{ 0, 0 }
};

extern "C" int luaopen_tiledata(lua_State *L)
{
	return luax_register_type(L, &TileData::type, functions, nullptr);
}

} // data
} // love
