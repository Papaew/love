
#ifndef LOVE_TABLET_TABLET_H
#define LOVE_TABLET_TABLET_H

// LOVE
#include "common/Module.h"

namespace love
{
namespace tablet
{

class Tablet : public Module
{
public:

	Tablet();
	virtual ~Tablet() {}

	/**
	 * Gets the average FPS over the last second. Beucase the value is only updated
	 * once per second, it does not look erratic when displayed on screen.
	 * @return The "current" FPS.
	**/
	int getFPS() const;

private:
	// Updated with a certain frequency.
	int fps;

}; // Tablet

} // tablet
} // love

#endif // LOVE_TABLET_TABLET_H
