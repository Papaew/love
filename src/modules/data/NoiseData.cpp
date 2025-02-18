#include "NoiseData.h"

namespace love
{
namespace data
{

love::Type NoiseData::type("NoiseData", &Object::type);

NoiseData::NoiseData(int width)
	: data((width) * (width) * sizeof(float))
	, x(0)
	, y(0)
{
}

NoiseData::~NoiseData()
{
}

const love::data::ByteData &NoiseData::getData() const
{
	return data;
}

void NoiseData::clear()
{
}

void NoiseData::setRandomState()
{
}

void NoiseData::set()
{
}

void NoiseData::setMode()
{
}

void NoiseData::getRandomState()
{
}

void NoiseData::get()
{
}

void NoiseData::generate()
{
	clear();
}

} // data
} // love
