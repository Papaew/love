
// LOVE
#include "common/config.h"
#include "Tablet.h"

namespace love
{
namespace tablet
{

Tablet::Tablet()
	: Module(M_TABLET, "love.tablet")
	, fps(0)
{
	// prevFpsUpdate = currTime = getTime();
}

int Tablet::getFPS() const
{
	return fps;
}

} // tablet
} // love
