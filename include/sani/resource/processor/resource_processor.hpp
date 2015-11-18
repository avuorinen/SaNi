#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, ResourceItem);

namespace sani {
	namespace resource {
		namespace processor {
			
			class ResourceProcessor {
			public:
				~ResourceProcessor() = default;
				virtual ResourceItem* process(ResourceItem* input) = 0;
				ResourceProcessor() = default;
			private:
				
			};
		}
	}
}
#endif