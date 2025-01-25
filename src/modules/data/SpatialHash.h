#ifndef LOVE_DATA_SPATIALHASH_H
#define LOVE_DATA_SPATIALHASH_H

// LOVE
#include "common/Object.h"
#include "ByteData.h"

#include <cstdint>

namespace love
{
namespace data
{

class SpatialHash : public Object
{
public:

	static love::Type type;

	SpatialHash(int maxObjectCount, float spacing);

	virtual ~SpatialHash();

	int add(float &x, float &y);
	void set(int index, float x, float y);
	bool get(int index, float &x, float &y);
	void query(float x, float y, float maxDist);
	void query(float x1, float y1, float x2, float y2);
	void clear();
	void process();

	const love::data::ByteData &getData() const;

private:
	float spacing;
	int tableSize;

	int *cellStart;
	int *cellEntries;
	int *queryIds;
	int querySize;

	int maxObjectCount;
	int objCount;

	love::data::ByteData data;
	float *pData;
}; // SpatialHash

} // namespace data
} // namespace love

#endif