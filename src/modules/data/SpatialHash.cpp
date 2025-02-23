#include "SpatialHash.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>

const int X_HASH_CONST = 73856093;
const int Y_HASH_CONST = 83492791;

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
	queryIds = new int[maxObjects];
	clear();
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
		int index = objCount * 2;
		pData[index] = x;
		pData[index + 1] = y;
		objCount++;
		return objCount - 1;
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

void SpatialHash::clear()
{
	memset(cellStart, 0, sizeof(int) * (tableSize + 1));
	memset(cellEntries, 0, sizeof(int) * maxObjectCount);
	memset(queryIds, 0, sizeof(int) * maxObjectCount);
	data.clear();
	querySize = 0;
	objCount = 0;
}

void SpatialHash::process()
{
	memset(cellStart, 0, sizeof(int) * (tableSize + 1));
	memset(cellEntries, 0, sizeof(int) * maxObjectCount);

	for (int i=0; i<objCount; i++)
	{
		int ix = std::floor(pData[i*2]   / spacing);
		int iy = std::floor(pData[i*2+1] / spacing);
		int h = hashCoords(ix, iy);
		cellStart[h]++;
	}

	int start = 0;
	for (int i=0; i<tableSize; i++)
	{
		start += cellStart[i];
		cellStart[i] = start;
	}
	cellStart[tableSize] = start; // guard

	for (int i=0; i < objCount; i++)
	{
		int ix = std::floor(pData[i*2]   / spacing);
		int iy = std::floor(pData[i*2+1] / spacing);
		int h = hashCoords(ix, iy);
		cellStart[h]--;
		cellEntries[cellStart[h]] = i;
	}
}

void SpatialHash::query(float x, float y, float maxDist)
{
	querySize = 0;
	if (objCount == 0)
		return;

	int x0 = std::floor((x - maxDist) / spacing);
	int y0 = std::floor((y - maxDist) / spacing);
	int x1 = std::floor((x + maxDist) / spacing);
	int y1 = std::floor((y + maxDist) / spacing);
	querySize = 0;
	
	for (int ix = x0; ix <= x1; ix++) {
	for (int iy = y0; iy <= y1; iy++) {
		int h = hashCoords(ix, iy);
		int start = cellStart[h];
		int end = cellStart[h+1];
		for (int i = start; i < end; i++) {
			queryIds[querySize] = cellEntries[i];
			querySize++;
		}
	}
	}
}

void SpatialHash::query(float fx1, float fy1, float fx2, float fy2)
{
	querySize = 0;
	if (objCount == 0)
		return;

	int x0 = std::floor(std::min(fx1, fx2) / spacing);
	int y0 = std::floor(std::min(fy1, fy2) / spacing);
	int x1 = std::floor(std::max(fx1, fx2) / spacing);
	int y1 = std::floor(std::max(fy1, fy2) / spacing);

	for (int ix = x0; ix <= x1; ix++) {
	for (int iy = y0; iy <= y1; iy++) {
		int h = hashCoords(ix, iy);
		int start = cellStart[h];
		int end = cellStart[h+1];
		for (int i = start; i < end; i++) {
			queryIds[querySize] = cellEntries[i];
			querySize++;
		}
	}
	}
}

int SpatialHash::getQuerySize() const
{
    return querySize;
}

int SpatialHash::getObjectCount() const
{
	return objCount;
}

const int* SpatialHash::getQueryIds() const
{
	return queryIds;
}

int SpatialHash::hashCoords(int x, int y)
{
	int h = (x * X_HASH_CONST) ^ (y * Y_HASH_CONST);
	return h % tableSize;
}

} // namespace data
} // namespace love
