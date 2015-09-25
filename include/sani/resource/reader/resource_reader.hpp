#pragma once
#include "sani/resource/resource_manager.hpp"
#include <sani/platform/binary_reader.hpp>

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
namespace sani {
	namespace resource {
		namespace reader {
			using namespace graphics;
			using namespace io;
			/// The class that handles reading single asset
			/// 
			/// @author siquel
			class ResourceReader : io::BinaryReader {
				// TODO add functions to read matrices vectors and stuff
			private:
				ResourceManager& manager;
				GraphicsDevice* graphicsDevice;
			public:
				/// Initializes new resource reader
				ResourceReader(const FileSystem* fs, const String& file, ResourceManager& manager, GraphicsDevice* device);
				~ResourceReader();

				/// Gets the global resource manager used in whole engine
				ResourceManager& getResourceManager() const;
				/// Gets the graphics device used in whole engine
				GraphicsDevice* getGraphicsDevice() const;
			};
		}
	}
}