#ifndef LOVE_DATA_NOISEDATA_H
#define LOVE_DATA_NOISEDATA_H

// LOVE
#include "common/Object.h"
#include "ByteData.h"

#include <cstdint>

namespace love
{
namespace data
{

class NoiseData : public Object
{
public:

	static love::Type type;

	NoiseData(int width);
	virtual ~NoiseData();

	void clear();
	void setRandomState();
	void set();
	void setMode();
	void getRandomState();
	void get();
	void generate();

	const love::data::ByteData &getData() const;

private:
	int x, y;
	int octaves;
	float amplitude;
	float frequency;
	float lacunarity;
	float persistence;

	love::data::ByteData data;
}; // NoiseData

} // namespace data
} // namespace love

#endif // LOVE_DATA_NOISEDATA_H
