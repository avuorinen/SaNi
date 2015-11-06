#pragma once
#include "sani/platform/file/binary_writer.hpp"
#include "sani/core/math/math.hpp"
#include <vector>
#include <typeindex>
#include <map>
SANI_FORWARD_DECLARE_2(sani, io, FileStream);
SANI_FORWARD_DECLARE_3(sani, resource, compiler, ResourceTypeWriter);
SANI_FORWARD_DECLARE_3(sani, resource, compiler, ResourceCompiler);
namespace sani {
	using namespace math;
	using namespace io;
	namespace resource {
		namespace compiler {
			class ResourceWriter : public io::BinaryWriter {
			private:
				static const char Platforms[];
				static const uint8 Version = 1;
				std::map<std::type_index, ResourceTypeWriter*> writers;
				const ResourceCompiler* compiler;

				// TODO this should be public
				template <class T>
				ResourceTypeWriter* getWriter();

				// TODO this needs to be public
				template <class T>
				void writeObject(const T* obj);

				/// Writes the header which consists of
				/// first 3 magic bytes S, N, B, then platform name
				/// and Version number
				void writeHeader();

				/// Writers the typewriters used to write this object
				void writeTypeWriters();
			public:

				// This assumes the file is opened already!
				ResourceWriter(const FileStream* stream, const ResourceCompiler* compiler);
				~ResourceWriter();

				/// TODO this is hax, we need streambuf or smthing
				/// Writes and flushes the object to stream
				/// @see ResourceWriter::writeHeader
				/// @see ResourceWriter::writeTypeWriters
				/// @see ResourceWriter::writeObject
				template <class T>
				void flush(const T* obj);

				template <class T>
				void writeContainer(const std::vector<T>& v);

				template <class T>
				void writeMatrix(const math::Matrix2<T>& mat);

				template <class T>
				void writeMatrix(const math::Matrix3<T>& mat);

				template <class T>
				void writeMatrix(const math::Matrix4<T>& mat);

				template <class T>
				void writeVector(const math::Vector2<T>& vec);

				template <class T>
				void writeVector(const math::Vector3<T>& vec);

				template <class T>
				void writeVector(const math::Vector4<T>& vec);
			};
		}
	}
}
#include "resource_writer.inl"