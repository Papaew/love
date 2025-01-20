#ifndef LOVE_DATA_SPATIALHASH_H
#define LOVE_DATA_SPATIALHASH_H

// LOVE
#include "common/Object.h"

#include <cstdint>

namespace love
{
namespace data
{

class SpatialHash : public Object
{
public:

	static love::Type type;

	SpatialHash(int maxObjects, float cellSize);

	virtual ~SpatialHash();

	void add(int32_t id, float x, float y);
	void query(float x, float y, float maxDist);
	void reset();

private:

	int maxObjects;
	float cellSize;
	int tableSize;

	int32_t* cellStart;
	int32_t* cellEntries;
	int32_t* queryIds;
	int querySize;

}; // SpatialHash

} // namespace data
} // namespace love

#endif