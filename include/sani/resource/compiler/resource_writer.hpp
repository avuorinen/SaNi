#pragma once
#include "sani/platform/binary_writer.hpp"
#include "sani/core/math/math.hpp"
SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
namespace sani {
	using namespace math;
	namespace resource {
		namespace compiler {
			class ResourceWriter : public io::BinaryWriter {
			private:
				static const char Platforms[];
				static const uint8 Version = 1;
			public:
				// TODO add functions to write matrices vectors and stuff
				// TODO this may need some wrapping
				// This assumes the file is opened already!
				ResourceWriter(FILE* file);
				~ResourceWriter();

				/// Writes the header which consists of
				/// first 3 magic bytes S, N, B, then platform name
				/// and Version number
				void writeHeader();
			};
		}
	}
}