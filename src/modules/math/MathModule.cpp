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

// LOVE
#include "MathModule.h"
#include "common/Vector.h"
#include "common/int.h"
#include "common/StringMap.h"
#include "BezierCurve.h"
#include "Transform.h"

#include "poly2tri/poly2tri.h"

// STL
#include <cmath>
#include <list>
#include <iostream>

// C
#include <time.h>

using std::list;
using love::Vector2;

namespace
{

// check if an angle is oriented counter clockwise
inline bool is_oriented_ccw(const Vector2 &a, const Vector2 &b, const Vector2 &c)
{
	// return det(b-a, c-a) >= 0
	return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) >= 0;
}

// check if a and b are on the same side of the line c->d
bool on_same_side(const Vector2 &a, const Vector2 &b, const Vector2 &c, const Vector2 &d)
{
	float px = d.x - c.x, py = d.y - c.y;
	// return det(p, a-c) * det(p, b-c) >= 0
	float l = px * (a.y - c.y) - py * (a.x - c.x);
	float m = px * (b.y - c.y) - py * (b.x - c.x);
	return l * m >= 0;
}

// checks is p is contained in the triangle abc
inline bool point_in_triangle(const Vector2 &p, const Vector2 &a, const Vector2 &b, const Vector2 &c)
{
	return on_same_side(p,a, b,c) && on_same_side(p,b, a,c) && on_same_side(p,c, a,b);
}

// checks if any vertex in `vertices' is in the triangle abc.
bool any_point_in_triangle(const std::list<const Vector2 *> &vertices, const Vector2 &a, const Vector2 &b, const Vector2 &c)
{
	for (const Vector2 *p : vertices)
	{
		if ((p != &a) && (p != &b) && (p != &c) && point_in_triangle(*p, a,b,c)) // oh god...
			return true;
	}

	return false;
}

inline bool is_ear(const Vector2 &a, const Vector2 &b, const Vector2 &c, const std::list<const Vector2 *> &vertices)
{
	return is_oriented_ccw(a,b,c) && !any_point_in_triangle(vertices, a,b,c);
}

double PerpendicularDistance(const love::Vector2 &pt, const love::Vector2 &lineStart, const love::Vector2 &lineEnd)
{
	double dx = lineEnd.x - lineStart.x;
	double dy = lineEnd.y - lineStart.y;

	//Normalise
	double mag = pow(pow(dx,2.0)+pow(dy,2.0),0.5);
	if(mag > 0.0)
	{
		dx /= mag; dy /= mag;
	}

	double pvx = pt.x - lineStart.x;
	double pvy = pt.y - lineStart.y;

	//Get dot product (project pv onto normalized direction)
	double pvdot = dx * pvx + dy * pvy;

	//Scale line direction vector
	double dsx = pvdot * dx;
	double dsy = pvdot * dy;

	//Subtract this from pv
	double ax = pvx - dsx;
	double ay = pvy - dsy;

	return pow(pow(ax,2.0)+pow(ay,2.0),0.5);
}

} // anonymous namespace

namespace love
{
namespace math
{

std::vector<Triangle> triangulate(const std::vector<love::Vector2> &polygon)
{
	if (polygon.size() < 3)
		throw love::Exception("Not a polygon");
	else if (polygon.size() == 3)
		return std::vector<Triangle>(1, Triangle(polygon[0], polygon[1], polygon[2]));

	// collect list of connections and record leftmost item to check if the polygon
	// has the expected winding
	std::vector<size_t> next_idx(polygon.size()), prev_idx(polygon.size());
	size_t idx_lm = 0;
	for (size_t i = 0; i < polygon.size(); ++i)
	{
		const love::Vector2 &lm = polygon[idx_lm], &p = polygon[i];
		if (p.x < lm.x || (p.x == lm.x && p.y < lm.y))
			idx_lm = i;
		next_idx[i] = i+1;
		prev_idx[i] = i-1;
	}
	next_idx[next_idx.size()-1] = 0;
	prev_idx[0] = prev_idx.size()-1;

	// check if the polygon has the expected winding and reverse polygon if needed
	if (!is_oriented_ccw(polygon[prev_idx[idx_lm]], polygon[idx_lm], polygon[next_idx[idx_lm]]))
		next_idx.swap(prev_idx);

	// collect list of concave polygons
	std::list<const love::Vector2 *> concave_vertices;
	for (size_t i = 0; i < polygon.size(); ++i)
	{
		if (!is_oriented_ccw(polygon[prev_idx[i]], polygon[i], polygon[next_idx[i]]))
			concave_vertices.push_back(&polygon[i]);
	}

	// triangulation according to kong
	std::vector<Triangle> triangles;
	size_t n_vertices = polygon.size();
	size_t current = 1, skipped = 0, next, prev;
	while (n_vertices > 3)
	{
		next = next_idx[current];
		prev = prev_idx[current];
		const Vector2 &a = polygon[prev], &b = polygon[current], &c = polygon[next];
		if (is_ear(a,b,c, concave_vertices))
		{
			triangles.push_back(Triangle(a,b,c));
			next_idx[prev] = next;
			prev_idx[next] = prev;
			concave_vertices.remove(&b);
			--n_vertices;
			skipped = 0;
		}
		else if (++skipped > n_vertices)
		{
			throw love::Exception("Cannot triangulate polygon.");
		}
		current = next;
	}
	next = next_idx[current];
	prev = prev_idx[current];
	triangles.push_back(Triangle(polygon[prev], polygon[current], polygon[next]));

	return triangles;
}

/**
 * https://en.wikipedia.org/wiki/Ramer–Douglas–Peucker_algorithm
 **/
void simplifyCurve(const std::vector<love::Vector2> &points, std::vector<love::Vector2> &out, double &epsilon)
{
	if (points.size() < 2)
		throw love::Exception("Need at least 2 vertices to simplify (got %d)", (int) points.size());

	// Find the point with the maximum distance from line between start and end
	double dmax = 0.0;
	size_t index = 0;
	size_t end = points.size()-1;
	for(size_t i = 1; i < end; i++)
	{
		double d = PerpendicularDistance(points[i], points[0], points[end]);
		if (d > dmax)
		{
			index = i;
			dmax = d;
		}
	}

	// If max distance is greater than epsilon, recursively simplify
	if(dmax > epsilon)
	{
		// Recursive call
		std::vector<love::Vector2> recResults1;
		std::vector<love::Vector2> recResults2;
		std::vector<love::Vector2> firstLine(points.begin(), points.begin()+index+1);
		std::vector<love::Vector2> lastLine(points.begin()+index, points.end());
		simplifyCurve(firstLine, recResults1, epsilon);
		simplifyCurve(lastLine, recResults2, epsilon);
 
		// Build the result list
		out.assign(recResults1.begin(), recResults1.end()-1);
		out.insert(out.end(), recResults2.begin(), recResults2.end());
		if (out.size() < 2)
			throw love::Exception("Problem assembling output");
	} 
	else 
	{
		//Just return start and end points
		out.clear();
		out.push_back(points[0]);
		out.push_back(points[end]);
	}
}

bool isConvex(const std::vector<love::Vector2> &polygon)
{
	if (polygon.size() < 3)
		return false;

	// a polygon is convex if all corners turn in the same direction
	// turning direction can be determined using the cross-product of
	// the forward difference vectors
	size_t i = polygon.size() - 2, j = polygon.size() - 1, k = 0;
	Vector2 p(polygon[j] - polygon[i]);
	Vector2 q(polygon[k] - polygon[j]);
	float winding = Vector2::cross(p, q);

	while (k+1 < polygon.size())
	{
		i = j; j = k; k++;
		p = polygon[j] - polygon[i];
		q = polygon[k] - polygon[j];

		if (Vector2::cross(p, q) * winding < 0)
			return false;
	}
	return true;
}

/**
 * http://en.wikipedia.org/wiki/SRGB#The_reverse_transformation
 **/
float gammaToLinear(float c)
{
	if (c <= 0.04045f)
		return c / 12.92f;
	else
		return powf((c + 0.055f) / 1.055f, 2.4f);
}

/**
 * http://en.wikipedia.org/wiki/SRGB#The_forward_transformation_.28CIE_xyY_or_CIE_XYZ_to_sRGB.29
 **/
float linearToGamma(float c)
{
	if (c <= 0.0031308f)
		return c * 12.92f;
	else
		return 1.055f * powf(c, 1.0f / 2.4f) - 0.055f;
}

float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

float eerp(float a, float b, float t)
{
	return pow(a * (b / a), t);
}

float invlerp(float a, float b, float t)
{
	return (t - a) / (b - a);
}

float inveerp(float a, float b, float t)
{
	return log(a / t) / log(a / b);
}

float dist2sq(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return dx * dx + dy * dy;
}

float dist3sq(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	float dz = z1 - z2;
	return dx * dx + dy * dy + dz * dz;
}

Math::Math()
	: Module(M_MATH, "love.math")
{
	RandomGenerator::Seed seed;
	seed.b64 = (uint64) time(nullptr);

	rng.set(new RandomGenerator(), Acquire::NORETAIN);
	rng->setSeed(seed);
}

Math::~Math()
{
}

RandomGenerator *Math::newRandomGenerator()
{
	return new RandomGenerator();
}

BezierCurve *Math::newBezierCurve(const std::vector<Vector2> &points)
{
	return new BezierCurve(points);
}

Transform *Math::newTransform()
{
	return new Transform();
}

Transform *Math::newTransform(float x, float y, float a, float sx, float sy, float ox, float oy, float kx, float ky, float fx, float fy)
{
	return new Transform(x, y, a, sx, sy, ox, oy, kx, ky, fx, fy);
}

} // math
} // love
