
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
	uint8_t value = (uint8_t) luaL_checkinteger(L, 4);
	t->setTileValue(ix, iy, value);
	return 0;
}

int w_TileData_setTileValueByIndex(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	int index = (int) luaL_checkinteger(L, 2);
	uint8_t value = (uint8_t) luaL_checkinteger(L, 3);
	t->setTileValueByIndex(index, value);
	return 0;
}

int w_TileData_setTileWeights(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	int ix = (int) luaL_checkinteger(L, 2);
	int iy = (int) luaL_checkinteger(L, 3);
	float E = (float) luaL_checknumber(L, 4);
	float F = (float) luaL_checknumber(L, 5);
	float J = (float) luaL_checknumber(L, 6);
	float K = (float) luaL_checknumber(L, 7);
	t->setTileWeights(ix, iy, E, F, J, K);
	return 0;
}

int w_TileData_setSurfaceLevel(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	float surface = (float) luaL_checknumber(L, 2);
	t->setSurfaceLevel(surface);
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

int w_TileData_getTileValueByIndex(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	int index = (int) luaL_checkinteger(L, 2);
	lua_pushnumber(L, (lua_Number) t->getTileValueByIndex(index));
	return 1;
}

int w_TileData_getTileWeights(lua_State *L)
{
	TileData *t = luax_checktiledata(L, 1);
	int ix = (int) luaL_checkinteger(L, 2);
	int iy = (int) luaL_checkinteger(L, 3);
	float E, F, J, K;
	t->getTileWeights(ix, iy, E, F, J, K);
	lua_pushnumber(L, (lua_Number) E);
	lua_pushnumber(L, (lua_Number) F);
	lua_pushnumber(L, (lua_Number) J);
	lua_pushnumber(L, (lua_Number) K);
	return 4;
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
	{ "setTileValueByIndex", w_TileData_setTileValueByIndex },
	{ "setTileWeights", w_TileData_setTileWeights },
	{ "setSurfaceLevel", w_TileData_setSurfaceLevel },
	
	{ "getWidth", w_TileData_getWidth },
	{ "getVirtualWidth", w_TileData_getVirtualWidth },
	{ "getTileValue", w_TileData_getTileValue },
	{ "getTileValueByIndex", w_TileData_getTileValueByIndex },
	{ "getTileWeights", w_TileData_getTileWeights },
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
