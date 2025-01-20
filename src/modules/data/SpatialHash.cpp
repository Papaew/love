#include "SpatialHash.h"
#include <cstring>
#include <cmath>

static int32_t hashCoords(float x, float y, int32_t tableSize)
{
	int32_t xi = static_cast<int32_t>(x);
	int32_t yi = static_cast<int32_t>(y);

	int32_t h = (xi * 73856093) ^ (yi * 83492791);
	// int32_t h = (xi * 92837111) ^ (yi * 689287499);
	return abs(h) % tableSize;
}

namespace love
{
namespace data
{

love::Type SpatialHash::type("SpatialHash", &Object::type);

SpatialHash::SpatialHash(int maxObjects, float cellSize)
	: maxObjects(maxObjects), cellSize(cellSize), tableSize(2 * maxObjects), querySize(0)
{
	cellStart = new int32_t[tableSize + 1];
	cellEntries = new int32_t[maxObjects];
	queryIds = new int32_t[maxObjects];
}

SpatialHash::~SpatialHash()
{
	delete[] cellStart;
	delete[] cellEntries;
	delete[] queryIds;
}

void SpatialHash::add(int32_t id, float x, float y)
{
	printf("SpatialHash add\n");
}

void SpatialHash::query(float x, float y, float maxDist)
{
	printf("SpatialHash query\n");
}

void SpatialHash::reset()
{
	memset(cellStart, 0, sizeof(int32_t) * (tableSize + 1));
    memset(cellEntries, 0, sizeof(int32_t) * maxObjects);
    memset(queryIds, 0, sizeof(int32_t) * maxObjects);
	querySize = 0;
}

} // data
} // love
