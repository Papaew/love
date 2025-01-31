
#ifndef LIMB_H
#define LIMB_H

// LOVE
#include "common/config.h"

namespace limb
{

#define LIMB_VERSION_STRING "0.0.55"
static const char *VERSION = LIMB_VERSION_STRING;

}

extern int luaopen_limb(lua_State *L);

#endif // LIMB_H
