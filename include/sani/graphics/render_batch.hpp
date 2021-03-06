#pragma once

#include "sani/platform/graphics/graphics_enums.hpp"
#include "sani/graphics/vertex_mode.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, RenderElementData);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderSetup);

namespace sani {

	namespace graphics {

		/// @class RenderBatch render_batch.hpp "sani/graphics/render_batch.hpp"
		/// @author voidbab
		/// 
		/// Represents a part of the rendering process.
		/// Can contain one or more elements that will be
		/// rendered.
		class RenderBatch final {
		public:
			// First vertex position in elements.
			uint32 verticesBegin;
			uint32 verticesCount;

			// First vertex index position in elements.
			uint32 indicesBegin;
			uint32 indicesCount;

			uint32 texture;
			uint32 effect;

			// Group of the batch, gets value from the first
			// renderable the batch gets.
			uint32 group;
			uint32 vertexElementsCount;

			// Setup/pipeline ID.
			uint32 renderSetup;

			// State elements.
			VertexMode vertexMode;
			RenderMode renderMode;

			RenderBatch();

			void resetBatch();

			~RenderBatch();
		};
	}
}