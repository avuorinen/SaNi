#include "sani/precompiled.hpp"
#include "sani/platform/graphics_device.hpp"

namespace sani {
	namespace graphics {

		/*
			TODO: create base Texture class that holds no dimensional data?
		*/

		/// @class Texture2D "sani/platform/texture2d
		class Texture2D {
		private:
			// Identifier of the texture, required atleast by the OpenGL.
			RenderTexture renderTexture;
			
			const uint32 width;
			const uint32 height;
		public:
			Texture2D(GraphicsDevice& device, const uint32 width, const uint32 height);

			// TODO: void setData(void* paskaa); ?

			uint32 getID() const;

			uint32 getWidth() const;
			uint32 getHeight() const;

			// TODO: add support for deleting the textures.
		};
	}
}