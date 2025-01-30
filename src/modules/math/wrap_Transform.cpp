/**
 * Copyright (c) 2006-2024 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#include "wrap_Transform.h"

namespace love
{
namespace math
{

Transform *luax_checktransform(lua_State *L, int idx)
{
	return luax_checktype<Transform>(L, idx, Transform::type);
}

void luax_checkmatrix(lua_State *L, int idx, Transform::MatrixLayout layout, float elements[16])
{
	bool columnmajor = layout == Transform::MATRIX_COLUMN_MAJOR;

	if (lua_istable(L, idx))
	{
		lua_rawgeti(L, idx, 1);
		bool tableoftables = lua_istable(L, -1);
		lua_pop(L, 1);

		if (tableoftables)
		{
			if (columnmajor)
			{
				for (int column = 0; column < 4; column++)
				{
					lua_rawgeti(L, idx, column + 1);

					for (int row = 0; row < 4; row++)
					{
						lua_rawgeti(L, -(row + 1), row + 1);
						elements[column * 4 + row] = (float) luaL_checknumber(L, -1);
					}

					lua_pop(L, 4 + 1);
				}
			}
			else
			{
				for (int row = 0; row < 4; row++)
				{
					lua_rawgeti(L, idx, row + 1);

					for (int column = 0; column < 4; column++)
					{
						// The table has the matrix elements laid out in row-major
						// order, but we need to store them column-major in memory.
						lua_rawgeti(L, -(column + 1), column + 1);
						elements[column * 4 + row] = (float) luaL_checknumber(L, -1);
					}

					lua_pop(L, 4 + 1);
				}
			}
		}
		else
		{
			if (columnmajor)
			{
				for (int column = 0; column < 4; column++)
				{
					for (int row = 0; row < 4; row++)
					{
						lua_rawgeti(L, idx, column * 4 + row + 1);
						elements[column * 4 + row] = (float) luaL_checknumber(L, -1);
					}
				}
			}
			else
			{
				for (int column = 0; column < 4; column++)
				{
					for (int row = 0; row < 4; row++)
					{
						// The table has the matrix elements laid out in row-major
						// order, but we need to store them column-major in memory.
						lua_rawgeti(L, idx, row * 4 + column + 1);
						elements[column * 4 + row] = (float) luaL_checknumber(L, -1);
					}
				}
			}

			lua_pop(L, 16);
		}
	}
	else
	{
		if (columnmajor)
		{
			for (int i = 0; i < 16; i++)
				elements[i] = (float) luaL_checknumber(L, idx + i);
		}
		else
		{
			for (int column = 0; column < 4; column++)
			{
				for (int row = 0; row < 4; row++)
					elements[column * 4 + row] = (float) luaL_checknumber(L, row * 4 + column + idx);
			}
		}
	}
}

int w_Transform_clone(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	Transform *newtransform = t->clone();
	luax_pushtype(L, newtransform);
	newtransform->release();
	return 1;
}

int w_Transform_inverse(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	Transform *inverse = t->inverse();
	luax_pushtype(L, inverse);
	inverse->release();
	return 1;
}

int w_Transform_apply(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	Transform *other = luax_checktransform(L, 2);
	t->apply(other);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_isAffine2DTransform(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	luax_pushboolean(L, t->getMatrix().isAffine2DTransform());
	return 1;
}

int w_Transform_translate(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float x = (float) luaL_checknumber(L, 2);
	float y = (float) luaL_checknumber(L, 3);
	t->translate(x, y);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_rotate(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float angle = (float) luaL_checknumber(L, 2);
	t->rotate(angle);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_scale(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float sx = (float) luaL_checknumber(L, 2);
	float sy = (float) luaL_optnumber(L, 3, sx);
	t->scale(sx, sy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_scaleX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float sx = (float) luaL_checknumber(L, 2);
	t->scale(sx, t->sy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_scaleY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float sy = (float) luaL_checknumber(L, 2);
	t->scale(t->sx, sy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_shear(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float kx = (float) luaL_checknumber(L, 2);
	float ky = (float) luaL_checknumber(L, 3);
	t->shear(kx, ky);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setPosition(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float x = (float) luaL_checknumber(L, 2);
	float y = (float) luaL_checknumber(L, 3);
	t->setPosition(x, y);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float x = (float) luaL_checknumber(L, 2);
	t->setPosition(x, t->y);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float y = (float) luaL_checknumber(L, 2);
	t->setPosition(t->x, y);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setFlip(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float fx = (float) luaL_checknumber(L, 2);
	float fy = (float) luaL_checknumber(L, 3);
	t->setFlip(fx, fy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setFlipX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float fx = (float) luaL_checknumber(L, 2);
	t->setFlip(fx, t->fy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setFlipY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float fy = (float) luaL_checknumber(L, 2);
	t->setFlip(t->fx, fy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setOrigin(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float ox = (float) luaL_checknumber(L, 2);
	float oy = (float) luaL_checknumber(L, 3);
	t->setOrigin(ox, oy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setOriginX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float ox = (float) luaL_checknumber(L, 2);
	t->setOrigin(ox, t->oy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setOriginY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float oy = (float) luaL_checknumber(L, 2);
	t->setOrigin(t->ox, oy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_getPosition(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->x);
	lua_pushnumber(L, t->y);
	return 2;
}

int w_Transform_getX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->x);
	return 1;
}

int w_Transform_getY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->y);
	return 1;
}

int w_Transform_getFlip(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->fx);
	lua_pushnumber(L, t->fy);
	return 2;
}

int w_Transform_getFlipX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->fx);
	return 1;
}

int w_Transform_getFlipY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->fy);
	return 1;
}

int w_Transform_getAngle(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->a);
	return 1;
}

int w_Transform_getScale(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->sx);
	lua_pushnumber(L, t->sy);
	return 2;
}

int w_Transform_getScaleX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->sx);
	return 1;
}

int w_Transform_getScaleY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->sy);
	return 1;
}

int w_Transform_getOrigin(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->ox);
	lua_pushnumber(L, t->oy);
	return 2;
}

int w_Transform_getOriginX(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->ox);
	return 1;
}

int w_Transform_getOriginY(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	lua_pushnumber(L, t->oy);
	return 1;
}

int w_Transform_reset(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	t->reset();
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setTransformation(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	float x =  (float) luaL_optnumber(L, 2, 0.0);
	float y =  (float) luaL_optnumber(L, 3, 0.0);
	float a =  (float) luaL_optnumber(L, 4, 0.0);
	float sx = (float) luaL_optnumber(L, 5, 1.0);
	float sy = (float) luaL_optnumber(L, 6, sx);
	float ox = (float) luaL_optnumber(L, 7, 0.0);
	float oy = (float) luaL_optnumber(L, 8, 0.0);
	float kx = (float) luaL_optnumber(L, 9, 0.0);
	float ky = (float) luaL_optnumber(L, 10, 0.0);
	float fx = (float) luaL_optnumber(L, 11, 1.0);
	float fy = (float) luaL_optnumber(L, 12, 1.0);
	t->setTransformation(x, y, a, sx, sy, ox, oy, kx, ky, fx, fy);
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_setMatrix(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	Transform::MatrixLayout layout = Transform::MATRIX_ROW_MAJOR;

	int idx = 2;
	if (lua_type(L, idx) == LUA_TSTRING)
	{
		const char *layoutstr = lua_tostring(L, idx);
		if (!Transform::getConstant(layoutstr, layout))
			return luax_enumerror(L, "matrix layout", Transform::getConstants(layout), layoutstr);

		idx++;
	}

	float elements[16];
	luax_checkmatrix(L, idx, layout, elements);

	t->setMatrix(Matrix4(elements));
	lua_pushvalue(L, 1);
	return 1;
}

int w_Transform_getMatrix(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	const float *elements = t->getMatrix().getElements();

	// We want to push elements in row-major order, but they're stored column-
	// major.
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
			lua_pushnumber(L, elements[column * 4 + row]);
	}

	return 16;
}

int w_Transform_transformPoint(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	love::Vector2 p;
	p.x = (float) luaL_checknumber(L, 2);
	p.y = (float) luaL_checknumber(L, 3);
	p = t->transformPoint(p);
	lua_pushnumber(L, p.x);
	lua_pushnumber(L, p.y);
	return 2;
}

int w_Transform_inverseTransformPoint(lua_State *L)
{
	Transform *t = luax_checktransform(L, 1);
	love::Vector2 p;
	p.x = (float) luaL_checknumber(L, 2);
	p.y = (float) luaL_checknumber(L, 3);
	p = t->inverseTransformPoint(p);
	lua_pushnumber(L, p.x);
	lua_pushnumber(L, p.y);
	return 2;
}

int w_Transform__mul(lua_State *L)
{
	Transform *t1 = luax_checktransform(L, 1);
	Transform *t2 = luax_checktransform(L, 2);
	Transform *t3 = new Transform(t1->getMatrix() * t2->getMatrix());
	luax_pushtype(L, t3);
	t3->release();
	return 1;
}

static const luaL_Reg functions[] =
{
	{ "clone", w_Transform_clone },
	{ "inverse", w_Transform_inverse },
	{ "apply", w_Transform_apply },
	{ "isAffine2DTransform", w_Transform_isAffine2DTransform },
	{ "translate", w_Transform_translate },
	{ "rotate", w_Transform_rotate },
	{ "scale", w_Transform_scale },
	{ "scaleX", w_Transform_scaleX },
	{ "scaleY", w_Transform_scaleY },
	{ "shear", w_Transform_shear },

	{ "setPosition", w_Transform_setPosition },
	{ "setX", w_Transform_setX },
	{ "setY", w_Transform_setY },
	{ "setFlip", w_Transform_setFlip },
	{ "setFlipX", w_Transform_setFlipX },
	{ "setFlipY", w_Transform_setFlipY },
	{ "setOrigin", w_Transform_setOrigin },
	{ "setOriginX", w_Transform_setOriginX },
	{ "setOriginY", w_Transform_setOriginY },

	{ "getPosition", w_Transform_getPosition },
	{ "getX", w_Transform_getX },
	{ "getY", w_Transform_getY },
	{ "getFlip", w_Transform_getFlip },
	{ "getFlipX", w_Transform_getFlipX },
	{ "getFlipY", w_Transform_getFlipY },
	{ "getAngle", w_Transform_getAngle },
	{ "getScale", w_Transform_getScale },
	{ "getScaleX", w_Transform_getScaleX },
	{ "getScaleY", w_Transform_getScaleY },
	{ "getOrigin", w_Transform_getOrigin },
	{ "getOriginX", w_Transform_getOriginX },
	{ "getOriginY", w_Transform_getOriginY },

	{ "reset", w_Transform_reset },
	{ "setTransformation", w_Transform_setTransformation },
	{ "setMatrix", w_Transform_setMatrix },
	{ "getMatrix", w_Transform_getMatrix },
	{ "transformPoint", w_Transform_transformPoint },
	{ "inverseTransformPoint", w_Transform_inverseTransformPoint },
	{ "__mul", w_Transform__mul },
	{ 0, 0 }
};

extern "C" int luaopen_transform(lua_State *L)
{
	return luax_register_type(L, &Transform::type, functions, nullptr);
}

} // math
} // love
