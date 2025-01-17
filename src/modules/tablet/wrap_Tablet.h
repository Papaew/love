
#ifndef LOVE_TABLET_WRAP_TABLET_H
#define LOVE_TABLET_WRAP_TABLET_H

// LOVE
#include "common/runtime.h"
#include "Tablet.h"

namespace love
{
namespace camera
{

extern "C" LOVE_EXPORT int luaopen_love_tablet(lua_State *L);

} // tablet
} // love

#endif // LOVE_TABLET_WRAP_TABLET_H
