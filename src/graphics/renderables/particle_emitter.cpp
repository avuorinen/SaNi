#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	namespace graphics {

		/*
			We are using a combination of sprites with the emitter.
			The emitter itself does not contain any vertex data,
			we only copy the data from the sprites to the emitters
			vertex data region. So the emitter is kinda just working
			as a "proxy" for the particles.
		*/

		const uint32 VERTICES_IN_SPRITE = 4;
		const uint32 INDICES_IN_SPRITE	= 6;

		ParticleEmitter::ParticleEmitter(const TextureList& textures, const uint32 maxParticles)
			: textures(textures), maxParticles(maxParticles), Renderable(VERTICES_IN_SPRITE * maxParticles, maxParticles * INDICES_IN_SPRITE, 1) {
			
			// Generate particles.
			SANI_ASSERT(textures.size() != 0);
			
			for (uint32 i = 0; i < maxParticles; i++) particles.push_back(Particle(*textures.begin()));
			
			// Generate indices.
			const uint32 indicesCount = maxParticles * INDICES_IN_SPRITE;

			for (uint32 i = 0; i < indicesCount; i += VERTICES_IN_SPRITE) {
				renderData.vertexIndices[i]		= i;
				renderData.vertexIndices[i + 1] = i + 1;
				renderData.vertexIndices[i + 2] = i + 2;
				
				renderData.vertexIndices[i + 3] = i + 2;
				renderData.vertexIndices[i + 4] = i + 1;
				renderData.vertexIndices[i + 5] = i + 3;
			}

			// Setup render element data.
			RenderElementData& particleRenderData = renderData.renderElements[0];
			particleRenderData.first = 0;
			particleRenderData.last = maxParticles * VERTICES_IN_SPRITE;
			particleRenderData.vertexElements = 9;
			particleRenderData.offset = 0;
			particleRenderData.indices = 6;

			// No need to compute bounds yet and no need to copy vertex data.
		}
	}
}