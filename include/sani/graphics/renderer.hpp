#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/graphics/vertex_mode.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/graphics/buffer.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		class GraphicsDevice;
		class RenderSetup;
		
		/// @class Renderer renderer.hpp "sani/graphics/renderer.hpp"
		/// @author voidbab
		///
		/// Low-level renderer of the rendering module. Uses different states
		/// to determine what will be rendered.
		class Renderer {
		private:
			// Device and setup states.
			GraphicsDevice& graphicsDevice;
			RenderSetup** renderSetups;
			RenderSetup* renderSetup;

			// API buffers.
			uint32 vertexBuffer;
			uint32 indexBuffer;

			// Renderer buffers.
			Buffer<float32> vertices;
			uint32 verticesSize;

			Buffer<uint32> indices;
			uint32 indicesSize;

			// Transform state and state.
			math::Mat4f transform;
			RenderState renderState;
			VertexMode vertexMode;

			void generateRenderSetups();
			void generateBuffers();

			void updateVertexBufferSize();
			void swapRenderSetup();

			void prepareRendering(const RenderState renderState, const math::Mat4f& transform, const VertexMode vertexMode);
			void prepareRenderingPolygons(const RenderMode renderMode, const uint32 elements);
			void prepareRenderingPolygons(const RenderMode renderMode, const uint32 texture, const uint32 elements);

			void endRendering(const RenderState renderState);

			void presentPolygons();
			void presentIndexedPolygons();
		public:
			Renderer(GraphicsDevice& graphicsDevice);

			bool initialize();

			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] texture texture that will be used to texture the shapes
			/// @param[in] elements how many elements each vertex has
			/// @param[in] renderMode render mode
			void beginRenderingPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 elements, const RenderMode renderMode);
			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] elements how many elements each vertex has
			/// @param[in] renderMode render mode
			void beginRenderingPolygons(const math::Mat4f& transform, const uint32 elements, const RenderMode renderMode);

			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] texture texture that will be used to texture the shapes
			/// @param[in] elements how many elements each vertex has
			/// @param[in] indices indices 
			/// @param[in] renderMode render mode
			void beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 elements, const uint32* indices, const RenderMode renderMode);
			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] elements how many elements each vertex has
			/// @param[in] indices indices
			/// @param[in] renderMode render mode
			void beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 elements, const uint32* indices, const RenderMode renderMode);

			/// Renders given polygons.
			/// @param[in] vertices vertices
			/// @param[in] count count of objects to render
			void renderPolygons(const float32* vertices, const uint32 count);
			/// Renders given polygon.
			/// @param[in] vertices vertices
			void renderPolygon(const float32* vertices);
			
			void endRendering();

			~Renderer();
		};
	}
}