#include "SpatialHash.h"
#include <iostream>
#include <cstring>
#include <cmath>

/* const int X_HASH_CONST = 73856093;
const int Y_HASH_CONST = 73856093;
static int hashCoords(float x, float y, int tableSize)
{
	int xi = static_cast<int>(x);
	int yi = static_cast<int>(y);

	int h = (xi * X_HASH_CONST) ^ (yi * Y_HASH_CONST);
	// int h = (xi * 92837111) ^ (yi * 689287499);
	return abs(h) % tableSize;
} */

namespace love
{
namespace data
{

love::Type SpatialHash::type("SpatialHash", &Object::type);

SpatialHash::SpatialHash(int maxObjects, float spacing)
	: data(maxObjects * sizeof(float) * 2)
	, pData(nullptr)
	, spacing(spacing)
	, maxObjectCount(maxObjects)
	, tableSize(2 * maxObjects)
	, querySize(0)
	, objCount(0)
{
	pData = static_cast<float *>(data.getData());
	cellStart = new int[tableSize + 1];
	cellEntries = new int[maxObjects];
	queryIds = new int[(int) maxObjects/2];
}

SpatialHash::~SpatialHash()
{
	delete[] cellStart;
	delete[] cellEntries;
	delete[] queryIds;

	pData = nullptr;
}

const love::data::ByteData &SpatialHash::getData() const
{
	return data;
}

int SpatialHash::add(float &x, float &y)
{
	if (objCount < maxObjectCount)
	{
		int index = objCount*2;
		pData[index] = x;
		pData[index+1] = y;
		objCount++;
		return objCount-1;
	}
	return -1;
}

void SpatialHash::set(int index, float x, float y)
{
	pData[index*2] = x;
	pData[index*2+1] = y;
}

bool SpatialHash::get(int index, float &x, float &y)
{
	bool acceptable = objCount > 0 && index >= 0 && index < objCount;
	if (acceptable)
	{
		x = pData[index*2];
		y = pData[index*2+1];
	}
	return acceptable;
}

void SpatialHash::query(float x, float y, float maxDist)
{
	printf("SpatialHash query\n");
}

void SpatialHash::query(float x1, float y1, float x2, float y2)
{
	printf("SpatialHash query\n");
}

void SpatialHash::clear()
{
	memset(cellStart, 0, sizeof(int) * (tableSize + 1));
	memset(cellEntries, 0, sizeof(int) * maxObjectCount);
	memset(queryIds, 0, sizeof(int) * maxObjectCount);
	querySize = 0;
	objCount = 0;
}

void SpatialHash::process()
{
	clear();
}

} // data
} // love
