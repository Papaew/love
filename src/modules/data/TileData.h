#ifndef LOVE_DATA_TILEDATA_H
#define LOVE_DATA_TILEDATA_H

// LOVE
#include "common/Object.h"
#include "ByteData.h"

#include <cstdint>

namespace love
{
namespace data
{

struct Tile
{
	int value;
	float E, F, J, K;
};

class TileData : public Object
{
public:

	static love::Type type;

	TileData(int width, float surface);
	virtual ~TileData();

	void clear();
	void generate();
	int getWidth();
	int getVirtualWidth();
	int getTileValue(int ix, int iy);
	float getSurfaceLevel();

	void setTileValue(int ix, int iy, int value);

	const love::data::ByteData &getData() const;

private:
	int width;
	float surface;

	love::data::ByteData data;
	Tile* tiles;
}; // TileData

} // namespace data
} // namespace love

#endif // LOVE_DATA_TILEDATA_H
