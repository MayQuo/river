#ifndef RIVER_INTERFACE_DRAWABLE_H
#define RIVER_INTERFACE_DRAWABLE_H

#include "../core.h"
#include "../app/application.h"

namespace river
{
	struct IDrawable
	{
		virtual void draw(const Application& app) = 0;
	};
}

#endif