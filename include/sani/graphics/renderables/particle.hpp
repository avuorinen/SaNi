#pragma once

#include "sani/core/math/vector2.hpp"
#include "sani/graphics/renderables/sprite.hpp"
#include "sani/platform/time/engine_time.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsEffect);
SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);
SANI_FORWARD_DECLARE_2(sani, graphics, Transform);

namespace sani {

	using namespace math;
	using namespace resource;

	namespace graphics {

		/// @class Particle particle.hpp "sani/graphics/renderables/particle.hpp"
		/// @author voidbab
		/// 
		/// Class that wraps all particle related information and the sprite 
		/// that serves as the visible part of the particle.
		class Particle final {
		private:
			const Vec2f velocity;
			const float32 timeToLive;
			const float32 angularVelocity;
			
			float32 elapsedTime;

			Sprite sprite;
		public:
			Particle(Texture2D* const texture, const Vec2f& position, const Vec2f& velocity, const float32 angle, 
					 const float32 angularVelocity, const Color& color, const Vec2f& size, const float32 timeToLive);

			/// Gets the sprite of the particle.
			Sprite& getSprite();

			/// Returns true if this particle is still alive.
			bool alive() const;

			/// Updates the particle.
			void update(const EngineTime& time);

			~Particle() = default;
		};
	}
}