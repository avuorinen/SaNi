#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		#define RENDER_STATES_COUNT 4

		enum RenderState : uint32 {
			// Renderer is waiting for user commands.
			Waiting				= 0,

			// Rendering predefined primitives.
			Polygons			= 1,
			
			// Rendering images.
			TexturedPolygons	= 2,
			
			// Rendering simple text.
			Text				= 3
		};
	}
}