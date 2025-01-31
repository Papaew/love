// LOVE
// #include "common/config.h"
#include "common/runtime.h"

#include "limb.h"

// Встраиваем все Lua-файлы
static const char limb_callback_lua[] = 
#include "limb/common/callback.lua"
;
static const char limb_drawable_lua[] = 
#include "limb/common/drawable.lua"
;
static const char limb_layer_lua[] = 
#include "limb/common/layer.lua"
;
static const char limb_luathread_lua[] = 
#include "limb/common/luathread.lua"
;
static const char limb_scene_lua[] = 
#include "limb/common/scene.lua"
;

static const char limb_class_lua[] = 
#include "limb/class.lua"
;
static const char limb_core_lua[] = 
#include "limb/core.lua"
;
static const char limb_renderer_lua[] = 
#include "limb/renderer.lua"
;
static const char limb_thread_lua[] = 
#include "limb/thread.lua"
;
static const char limb_scenes_lua[] = 
#include "limb/scenes.lua"
;
static const char limb_callbacks_lua[] = 
#include "limb/callbacks.lua"
;

extern "C"
{
	extern int luaopen_limb_class(lua_State *);
	extern int luaopen_limb_renderer(lua_State *);
	extern int luaopen_limb_thread(lua_State *);
	extern int luaopen_limb_scenes(lua_State *);
	extern int luaopen_limb_callbacks(lua_State *);

	extern int luaopen_limb_callback(lua_State *);
	extern int luaopen_limb_drawable(lua_State *);
	extern int luaopen_limb_scene(lua_State *);
	extern int luaopen_limb_luathread(lua_State *);
	extern int luaopen_limb_layer(lua_State *);
}

static const luaL_Reg modules[] = {
	{ "class", luaopen_limb_class },
	{ "limb.renderer", luaopen_limb_renderer },
	{ "limb.thread", luaopen_limb_thread },
	{ "limb.scenes", luaopen_limb_scenes },
	{ "limb.callbacks", luaopen_limb_callbacks },

	{ "limb.common.callback", luaopen_limb_callback },
	{ "limb.common.drawable", luaopen_limb_drawable },
	{ "limb.common.scene", luaopen_limb_scene },
	{ "limb.common.luathread", luaopen_limb_luathread },
	{ "limb.common.layer", luaopen_limb_layer },
	{ 0, 0 }
};

// Функция для загрузки Lua-модуля из встроенного массива
static int load_lua_module(lua_State *L, const char *code, size_t code_len, const char *name)
{
	// Загружаем Lua-код из буфера
	if (luaL_loadbuffer(L, code, code_len, name) != 0)
		return lua_error(L);

	if (lua_pcall(L, 0, 1, 0) != 0)
		return lua_error(L);

	return 1;
}

int luaopen_limb_callback(lua_State *L) { return load_lua_module(L, limb_callback_lua, sizeof(limb_callback_lua) - 1, "=[limb \"callback.lua\"]"); }
int luaopen_limb_drawable(lua_State *L) { return load_lua_module(L, limb_drawable_lua, sizeof(limb_drawable_lua) - 1, "=[limb \"drawable.lua\"]"); }
int luaopen_limb_scene(lua_State *L) { return load_lua_module(L, limb_scene_lua, sizeof(limb_scene_lua) - 1, "=[limb \"scene.lua\"]"); }
int luaopen_limb_luathread(lua_State *L) { return load_lua_module(L, limb_luathread_lua, sizeof(limb_luathread_lua) - 1, "=[limb \"luathread.lua\"]"); }
int luaopen_limb_layer(lua_State *L) { return load_lua_module(L, limb_layer_lua, sizeof(limb_layer_lua) - 1, "=[limb \"layer.lua\"]"); }

int luaopen_limb_class(lua_State *L) { return load_lua_module(L, limb_class_lua, sizeof(limb_class_lua) - 1, "=[limb \"class.lua\"]"); }
int luaopen_limb_renderer(lua_State *L) { return load_lua_module(L, limb_renderer_lua, sizeof(limb_renderer_lua) - 1, "=[limb \"renderer.lua\"]"); }
int luaopen_limb_thread(lua_State *L) { return load_lua_module(L, limb_thread_lua, sizeof(limb_thread_lua) - 1, "=[limb \"thread.lua\"]"); }
int luaopen_limb_scenes(lua_State *L) { return load_lua_module(L, limb_scenes_lua, sizeof(limb_scenes_lua) - 1, "=[limb \"scenes.lua\"]"); }
int luaopen_limb_callbacks(lua_State *L) { return load_lua_module(L, limb_callbacks_lua, sizeof(limb_callbacks_lua) - 1, "=[limb \"callbacks.lua\"]"); }

int luaopen_limb(lua_State *L)
{
	for (int i = 0; modules[i].name != nullptr; i++)
		love::luax_preload(L, modules[i].func, modules[i].name);

	love::luax_insistglobal(L, "limb");

	lua_pushstring(L, limb::VERSION);
	lua_setfield(L, -2, "_version");

	// love::luax_preload(L, luaopen_limb_class, "class");
	load_lua_module(L, limb_core_lua, sizeof(limb_core_lua) - 1, "=[limb \"core.lua\"]");

	return 1;
}
