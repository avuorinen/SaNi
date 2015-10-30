#pragma once

namespace sani {

	/// Defines how the heap allocator should 
	/// be defragmented.
	enum DefragmentationPolicy {
		/// Automatic defragmentations. Pages are
		/// defragmented if their fragmentation
		/// is larger or equal to 10%.
		Automatic,

		/// Manual defragmentation. User must 
		/// manage defragmentation calls.
		Manual
	};
}