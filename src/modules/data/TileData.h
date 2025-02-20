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
	uint8_t value;
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
	int getTileValueByIndex(int index);
	void setTileWeights(int ix, int iy, float E, float F, float J, float K);
	float getSurfaceLevel();

	void setTileValue(int ix, int iy, uint8_t value);
	void setTileValueByIndex(int index, uint8_t value);
	void getTileWeights(int ix, int iy, float &E, float &F, float &J, float &K);
	void setSurfaceLevel(float surface);

	const love::data::ByteData &getData() const;
	Tile* getTiles();

private:
	int width;
	float surface;

	love::data::ByteData data;
	Tile* tiles;
}; // TileData

} // namespace data
} // namespace love

#endif // LOVE_DATA_TILEDATA_H
