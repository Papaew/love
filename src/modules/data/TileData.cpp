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

void TileData::setTileValue(int ix, int iy, uint8_t value)
{
	int index = iy * width + ix;
	tiles[index].value = value;
}

void TileData::setTileValueByIndex(int index, uint8_t value)
{
	tiles[index].value = value;
}

void TileData::setTileWeights(int ix, int iy, float E, float F, float J, float K)
{
	int index = iy * width + ix;
	tiles[index].E = E;
	tiles[index].F = F;
	tiles[index].J = J;
	tiles[index].K = K;
}

void TileData::setSurfaceLevel(float surface)
{
	this->surface = surface;
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

int TileData::getTileValueByIndex(int index)
{
	return tiles[index].value;
}

void TileData::getTileWeights(int ix, int iy, float &E, float &F, float &J, float &K)
{
	int index = iy * width + ix;
	E = tiles[index].E;
	F = tiles[index].F;
	J = tiles[index].J;
	K = tiles[index].K;
}

Tile* TileData::getTiles() {
	return tiles;
}

} // data
} // love
