#include "TileData.h"

namespace love
{
namespace data
{

love::Type TileData::type("TileData", &Object::type);

TileData::TileData(int width, float surface)
	: data((width+2) * (width+2) * sizeof(Tile))
	, width(width+2)
	, surface(surface)
{
	tiles = reinterpret_cast<Tile*>(data.getData());
}

TileData::~TileData()
{
	// todo
}

const love::data::ByteData &TileData::getData() const
{
	return data;
}

void TileData::clear()
{
	data.clear();
}

void TileData::generate()
{
	int index = 0;
	for (int ix = 0; ix < width; ix++) {
	for (int iy = 0; iy < width; iy++) {
		index = iy * width + ix;
		tiles[index].value = index+1;
	}
	}
}

void TileData::setTileValue(int ix, int iy, int value)
{
	int index = iy * width + ix;
	tiles[index].value = value;
}

int TileData::getWidth()
{
	return width-2;
}

int TileData::getVirtualWidth()
{
	return width;
}

float TileData::getSurfaceLevel()
{
	return surface;
}

int TileData::getTileValue(int ix, int iy)
{
	int index = iy * width + ix;
	return tiles[index].value;
}

} // data
} // love
