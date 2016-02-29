#pragma once

#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, SpriteFont);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {

	namespace graphics {
		
		const uint32 TokenVertices	= 4;
		const uint32 TokenIndices	= 6;
		const uint32 TokenElements	= 9;

		class StaticText final : public Renderable {
		public:
			GraphicsDevice* const device;

			RenderTarget2D renderTarget;
			resource::SpriteFont* font;
			
			String16 text;
			Color color;

			StaticText(GraphicsDevice* const device, resource::SpriteFont* const font, const float32 x, const float32 y, const float32 w, const float32 h);
			StaticText(GraphicsDevice* const device, resource::SpriteFont* const font, const math::Vec2f& position, const math::Vec2f& size);
			StaticText(GraphicsDevice* const device, resource::SpriteFont* const font, const math::Rect32f& bounds);

			~StaticText();
		};

		inline void setText(StaticText& staticText, const String16& text);

		inline void recomputeVertices(StaticText& staticText);
		inline void recomputeBounds(StaticText& staticText);

		inline void updateRenderData(StaticText& staticText);
	}
}

#include "sani/graphics/renderables/static_text.hpp"