#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include <vector>

namespace sani {

	namespace graphics {
		
		#define VERTICES_ROUGH_CIRCLE	9
		#define VERTICES_SMOOTH_CIRCLE	36

		class Circle : public Renderable {
		public:
			float32 borderThickness;
			Color borderFill;
			
			float32 radius;
			Color fill;

			uint32 vertices;

			Circle(const float32 x, const float32 y, const float32 radius, const uint32 vertices);
			Circle(const sani::math::Vec2f& position, const float32 radius, const uint32 vertices);
			Circle(const float32 radius, const uint32 vertices);
			Circle(const float32 radius);
		};

		inline void recomputeGeometryData(Circle& circle);
		inline void recomputeVertices(Circle& circle);
		inline void recomputeBounds(Circle& circle);

		inline void updateRenderData(Circle& circle);
	}
}

#include "sani/graphics/inl/circle.inl"