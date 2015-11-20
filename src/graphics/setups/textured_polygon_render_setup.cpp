#include "sani/graphics/setups/textured_polygon_render_setup.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {

	namespace graphics {

		TexturedPolygonRenderSetup::TexturedPolygonRenderSetup(GraphicsDevice* const graphicsDevice) : PolygonRenderSetup(graphicsDevice) {
			// No need to set default render mode, base sets it.
		}

		void TexturedPolygonRenderSetup::use()  {
			PolygonRenderSetup::use();

			VertexAttributePointerDescription textureDescription;
			textureDescription.location = 2;
			textureDescription.count = 2;
			textureDescription.type = PrimitiveType::Float;
			textureDescription.normalized = false;
			textureDescription.stride = sizeof(float32) * getVertexElementsCount();
			textureDescription.offset = sizeof(float32) * 7;

			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->createVertexAttributePointer(textureDescription);
		}

		void TexturedPolygonRenderSetup::clear() {
			PolygonRenderSetup::clear();

			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->disableVertexAttributePointer(2);
		}
	}
}