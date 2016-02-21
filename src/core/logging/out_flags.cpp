#include "sani/core/logging/out_flags.hpp"

namespace sani {

	namespace log {

#define CAST_ARGS const uint32 a = static_cast<uint32>(lhs); \
				  const uint32 b = static_cast<uint32>(rhs) \

		OutFlags operator &(const OutFlags lhs, const OutFlags rhs) {
			CAST_ARGS;

			return static_cast<OutFlags>(a & b);
		}

		/*
			TODO: add more operators if needed.
		*/
	}
}