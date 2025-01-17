
#ifndef LOVE_CAMERA_WRAP_CAMERA_H
#define LOVE_CAMERA_WRAP_CAMERA_H

// LOVE
#include "common/runtime.h"
#include "Camera.h"

namespace love
{
namespace camera
{

extern "C" LOVE_EXPORT int luaopen_love_camera(lua_State *L);

} // camera
} // love

#endif // LOVE_CAMERA_WRAP_CAMERA_H
