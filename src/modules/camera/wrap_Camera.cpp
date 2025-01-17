
#include "common/config.h"

// LOVE
#include "wrap_Camera.h"

namespace love
{
namespace camera
{

#define instance() (Module::getInstance<Camera>(Module::M_CAMERA))

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


extern "C" int luaopen_love_camera(lua_State *L)
{
	Camera *instance = instance();
	if (instance == nullptr)
	{
		luax_catchexcept(L, [&](){ instance = new love::camera::Camera(); });
	}
	else
		instance->retain();

	WrappedModule w;
	w.module = instance;
	w.name = "camera";
	w.type = &Module::type;
	w.functions = functions;
	w.types = 0;

	return luax_register_module(L, w);
}

} // camera
} // love
