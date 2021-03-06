#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include "sani/platform/file/file_stream.hpp"
#include <cstdio>
SANI_FORWARD_DECLARE_2(sani, io, FileStream);

namespace sani {
	namespace io {
		class BinaryWriter {
			// hax much?
		protected:
			Stream* stream;
		public:
			BinaryWriter(Stream* stream);
			~BinaryWriter();
			void flush() const;
			void write(uint8 value);
			void write(uint16 value);
			void write(uint32 value);
			void write(uint64 value);
			void write(int8 value);
			void write(int16 value);
			void write(int32 value);
			void write(int64 value);
			void write(float32 value);
			void write(float64 value);
			void write(const String& value);
			void write7BitEncodedInt(uint64 value);
		};
	}
}