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

#include "Transform.h"

namespace love
{
namespace math
{

love::Type Transform::type("Transform", &Object::type);

Transform::Transform()
	: matrix()
	, inverseDirty(true)
	, inverseMatrix()
	, x(0), y(0), a(0), sx(1), sy(1), ox(0), oy(0), kx(0), ky(0), fx(1), fy(1)
{
}

Transform::Transform(const Matrix4 &m)
	: matrix(m)
	, inverseDirty(true)
	, inverseMatrix()
	, x(0), y(0), a(0), sx(1), sy(1), ox(0), oy(0), kx(0), ky(0), fx(1), fy(1)
{
}

Transform::Transform(float x, float y, float a, float sx, float sy, float ox, float oy, float kx, float ky, float fx, float fy)
	: matrix(x, y, a, sx, sy, ox, oy, kx, ky)
	, inverseDirty(true)
	, inverseMatrix()
	, x(x), y(y), a(a), sx(sx), sy(sy), ox(ox), oy(oy), kx(kx), ky(ky), fx(fx), fy(fy)
{
}

Transform::~Transform()
{
}

Transform *Transform::clone()
{
	return new Transform(*this);
}

Transform *Transform::inverse()
{
	return new Transform(getInverseMatrix());
}

void Transform::refresh()
{
	matrix.setIdentity();
	matrix.translate(x, y);
	matrix.rotate(a);
	matrix.scale(sx*fx, sy*fy);
	matrix.shear(kx, ky);
	matrix.translate(-ox, -oy);
	inverseDirty = true;
}

void Transform::apply(Transform *other)
{
	matrix *= other->getMatrix();
	inverseDirty = true;
}

void Transform::translate(float x, float y)
{
	this->x += x;
	this->y += y;
	// matrix.translate(x, y);
	// inverseDirty = true;
	refresh();
}

void Transform::rotate(float angle)
{
	this->a += angle;
	// matrix.rotate(angle);
	// inverseDirty = true;
	refresh();
}

void Transform::scale(float x, float y)
{
	this->sx += x;
	this->sy += y;
	// matrix.scale(sx, sy);
	// inverseDirty = true;
	refresh();
}

void Transform::shear(float x, float y)
{
	this->kx = x;
	this->ky = y;
	// matrix.shear(x, y);
	// inverseDirty = true;
	refresh();
}

void Transform::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	refresh();
}

void Transform::setFlip(float x, float y)
{
	this->fx = x;
	this->fy = y;
	refresh();
}

void Transform::setOrigin(float x, float y)
{
	this->ox = x;
	this->oy = y;
	refresh();
}

void Transform::reset()
{
	matrix.setIdentity();
	x=0, y=0, a=0, sx=1, sy=1, ox=0, oy=0, kx=0, ky=0, fx=1, fy=1;
	inverseDirty = true;
}

void Transform::setTransformation(float x, float y, float a, float sx, float sy, float ox, float oy, float kx, float ky, float fx, float fy)
{
	matrix.setTransformation(x, y, a, sx*fx, sy*fy, ox, oy, kx, ky);
	this->x=x, this->y=y;
	this->a=a;
	this->sx=sx, this->sy=sy;
	this->ox=ox, this->oy=oy;
	this->kx=kx, this->ky=ky;
	this->fx=fx, this->fy=fy;
	inverseDirty = true;
}

love::Vector2 Transform::transformPoint(love::Vector2 p) const
{
	love::Vector2 result;
	matrix.transformXY(&result, &p, 1);
	return result;
}

love::Vector2 Transform::inverseTransformPoint(love::Vector2 p)
{
	love::Vector2 result;
	getInverseMatrix().transformXY(&result, &p, 1);
	return result;
}

const Matrix4 &Transform::getMatrix() const
{
	return matrix;
}

void Transform::setMatrix(const Matrix4 &m)
{
	matrix = m;
	inverseDirty = true;
}

bool Transform::getConstant(const char *in, MatrixLayout &out)
{
	return matrixLayouts.find(in, out);
}

bool Transform::getConstant(MatrixLayout in, const char *&out)
{
	return matrixLayouts.find(in, out);
}

std::vector<std::string> Transform::getConstants(MatrixLayout)
{
	return matrixLayouts.getNames();
}

StringMap<Transform::MatrixLayout, Transform::MATRIX_MAX_ENUM>::Entry Transform::matrixLayoutEntries[] =
{
	{ "row",    MATRIX_ROW_MAJOR    },
	{ "column", MATRIX_COLUMN_MAJOR },
};

StringMap<Transform::MatrixLayout, Transform::MATRIX_MAX_ENUM> Transform::matrixLayouts(Transform::matrixLayoutEntries, sizeof(Transform::matrixLayoutEntries));

} // math
} // love
