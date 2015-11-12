#pragma once	

namespace sani {

	namespace graphics {

		enum class VertexMode {
			// Vertices are drawn without indexing.
			NoIndexing,
			// Vertices are drawn using indexing. 
			Indexed
		};
	}
}