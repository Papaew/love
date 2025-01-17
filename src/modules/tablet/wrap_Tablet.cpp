
#include "common/config.h"

// LOVE
#include "wrap_Tablet.h"

namespace love
{
namespace tablet
{

#define instance() (Module::getInstance<Tablet>(Module::M_TABLET))

int w_getFPS(lua_State *L)
{
	lua_pushinteger(L, instance()->getFPS());
	return 1;
}

// List of functions to wrap.
static const luaL_Reg functions[] =
{
	{ "getFPS", w_getFPS },
	{ 0, 0 }
};


extern "C" int luaopen_love_tablet(lua_State *L)
{
	Tablet *instance = instance();
	if (instance == nullptr)
	{
		luax_catchexcept(L, [&](){ instance = new love::tablet::Tablet(); });
	}
	else
		instance->retain();

	WrappedModule w;
	w.module = instance;
	w.name = "tablet";
	w.type = &Module::type;
	w.functions = functions;
	w.types = 0;

	return luax_register_module(L, w);
}

} // tablet
} // love
