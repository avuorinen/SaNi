#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		#define INITIAL_BUFFER_ELEMENTS_COUNT 32768
		#define REQUIRE_STATE(requiredState) if (state != requiredState) throw std::runtime_error("can't call function " + String(__FUNCTION__) + " in current state");

		// For starters, reserve 128kb worth of vertex memory (32768 float32 elements).
		// Keep the buffer usage as dynamic (memory as the limit).

		Renderer::Renderer(GraphicsDevice& graphicsDevice) : graphicsDevice(graphicsDevice),
															 vertices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
															 indices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
															 renderState(RenderState::Waiting),
															 vertexBuffer(0),
															 indexBuffer(0) {
		}

		void Renderer::generateRenderSetups() {
			renderSetups = new RenderSetup*[RENDER_STATES_COUNT];
			
			renderSetups[RenderState::Waiting]			= nullptr;												
			renderSetups[RenderState::Polygons]			= new PolygonRenderSetup(&graphicsDevice); 		
			renderSetups[RenderState::TexturedPolygons]	= new TexturedPolygonRenderSetup(&graphicsDevice);												
			renderSetups[RenderState::Text]				= new TexturedPolygonRenderSetup(&graphicsDevice);												
		}
		void Renderer::generateBuffers() {
			graphicsDevice.generateBuffer(vertexBuffer);
			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice.generateBuffer(indexBuffer);
			graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

			graphicsDevice.setBufferData(BufferType::ArrayBuffer,
										 vertices.getSize() * sizeof(float32),
										 vertices.head(),
										 BufferUsage::Stream);


			graphicsDevice.setBufferData(BufferType::ElementArrayBuffer,
										 vertices.getSize() * sizeof(float32),
										 vertices.head(),
										 BufferUsage::Stream);
		}

		void Renderer::updateVertexBufferSize() {
			// Rebind buffer if it's size has changed.
			if (verticesSize != vertices.getSize()) {
				graphicsDevice.setBufferData(BufferType::ArrayBuffer,
											 vertices.getSize() * sizeof(float32),
											 vertices.head(),
											 BufferUsage::Stream);

				verticesSize = vertices.getSize();
			}
		}
		void Renderer::swapRenderSetup() {
			const uint32 index = static_cast<uint32>(renderState);

			renderSetup = renderSetups[index];
		}
		
		void Renderer::prepareRendering(const RenderState renderState, const math::Mat4f& transform, const VertexMode vertexMode) {
			if (this->renderState != RenderState::Waiting) throw std::runtime_error("end rendering must be called before begin");

			this->renderState = renderState;
			this->transform = transform;
			this->vertexMode = vertexMode;
			
			vertices.resetBufferPointer();
		}
		void Renderer::prepareRenderingPolygons(const RenderMode renderMode, const uint32 vertices) {
			swapRenderSetup();

			PolygonRenderSetup* const polygonRenderSetup = static_cast<PolygonRenderSetup*>(renderSetup);
			polygonRenderSetup->setRenderMode(renderMode);
			polygonRenderSetup->setVertices(vertices);
		}
		void Renderer::prepareRenderingPolygons(const RenderMode renderMode, const uint32 texture, const uint32 vertices) {
			prepareRenderingPolygons(renderMode, vertices);
			
			TexturedPolygonRenderSetup* const polygonRenderSetup = static_cast<TexturedPolygonRenderSetup*>(renderSetup);
			polygonRenderSetup->setTexture(texture);
		}

		void Renderer::endRendering(const RenderState renderState) {
			if (renderState == RenderState::Waiting) throw std::runtime_error("begin rendering must be called before end");

			this->renderState = RenderState::Waiting;
			
			renderSetup->clear();
		}

		void Renderer::presentPolygons() {
			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);
			
			updateVertexBufferSize();

			graphicsDevice.setBufferSubData(BufferType::ArrayBuffer,
											0,
											vertices.getBufferPointerLocation() * sizeof(float32),
											vertices.head());

			PolygonRenderSetup* renderSetup = static_cast<PolygonRenderSetup*>(this->renderSetup);

			graphicsDevice.drawArrays(renderSetup->getRenderMode(), 0, vertices.getBufferPointerLocation() / renderSetup->getVertices());
		}
		void Renderer::presentIndexedPolygons() {
			throw std::runtime_error("not implemented");
		}

		bool Renderer::initialize() {
			generateRenderSetups();
			generateBuffers();

			return graphicsDevice.hasErrors();
		}

		void Renderer::beginRenderingPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 vertices, const RenderMode renderMode) {
			SANI_ASSERT(vertices != 0);

			prepareRendering(RenderState::TexturedPolygons, transform, VertexMode::NoIndexing);
			prepareRenderingPolygons(renderMode, texture, vertices);
			
			renderSetup->use();
		}
		void Renderer::beginRenderingPolygons(const math::Mat4f& transform, const uint32 vertices, const RenderMode renderMode) {
			SANI_ASSERT(vertices != 0);
			
			prepareRendering(RenderState::Polygons, transform, VertexMode::NoIndexing);
			prepareRenderingPolygons(renderMode, vertices);

			renderSetup->use();
		}
		
		void Renderer::beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 vertices, const uint32* indices, const RenderMode renderMode) {
			throw std::runtime_error("not implemented");
		}
		void Renderer::beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 vertices, const uint32* indices, const RenderMode renderMode) {
			throw std::runtime_error("not implemented");
		}
		
		void Renderer::renderPolygons(const float32* vertices, const uint32 count) {
			PolygonRenderSetup* const polygonRenderSetup = static_cast<PolygonRenderSetup*>(renderSetup);
			
			this->vertices.push(vertices, count * polygonRenderSetup->getVertices());

			// TODO: make indices.
		}
		void Renderer::renderPolygon(const float32* vertices) {
			PolygonRenderSetup* const polygonRenderSetup = static_cast<PolygonRenderSetup*>(renderSetup);

			this->vertices.push(vertices, polygonRenderSetup->getVertices());

			// TODO: make indices.
		}

		void Renderer::endRendering() {
			switch (renderState) {
			case sani::graphics::RenderState::Polygons:
				if (vertexMode == VertexMode::NoIndexing) presentPolygons();
				else                                      presentIndexedPolygons();
				break;
			case sani::graphics::RenderState::TexturedPolygons:
			case sani::graphics::RenderState::Waiting:
			case sani::graphics::RenderState::Text:
			default:
				throw std::runtime_error("invalid or unsupported state");
			}

			endRendering(renderState);
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RENDER_STATES_COUNT; i++) delete renderSetups[i];
			
			delete[]renderSetups;
		}
	}
}