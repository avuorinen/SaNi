#pragma once

#include <sani/platform/platform_config.hpp>

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
#include <sstream>

namespace std {
	template <typename T>
	String to_string(const T& value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}
}
#endif
