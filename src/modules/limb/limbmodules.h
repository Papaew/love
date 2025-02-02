#ifndef LIMB_LUA_MODULES_H
#define LIMB_LUA_MODULES_H

namespace limb
{

static const char callback_lua[] = 
#include "limb/common/callback.lua"
;
static const char drawable_lua[] = 
#include "limb/common/drawable.lua"
;
static const char layer_lua[] = 
#include "limb/common/layer.lua"
;
static const char luathread_lua[] = 
#include "limb/common/luathread.lua"
;
static const char scene_lua[] = 
#include "limb/common/scene.lua"
;

static const char class_lua[] = 
#include "limb/class.lua"
;
static const char core_lua[] = 
#include "limb/core.lua"
;
static const char renderer_lua[] = 
#include "limb/renderer.lua"
;
static const char thread_lua[] = 
#include "limb/thread.lua"
;
static const char scenes_lua[] = 
#include "limb/scenes.lua"
;
static const char callbacks_lua[] = 
#include "limb/callbacks.lua"
;

} // namespace limb

#endif // LIMB_LUA_MODULES_H
