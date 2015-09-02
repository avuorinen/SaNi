#include "sani/platform/graphics_device.hpp"
#include "sani/platform/render_target.h"

namespace sani {
	namespace graphics {

		// Init functions per platform and API.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
		// Win32 OpenGL implementation.

		RenderTarget2D::RenderTarget2D(GraphicsDevice& device, const uint32 width, const uint32 height) : Texture2D(device, width, height),
																										  frameBuffer(0),
																										  colorBuffer(0),
																										  depthBuffer(0) {
		}

		// TODO: add directx support.
#endif

		Buffer RenderTarget2D::getColorBuffer() const {
			return colorBuffer;
		}
		Buffer RenderTarget2D::getDepthBuffer() const {
			return depthBuffer;
		}
	}
}