#pragma once

#include "sani/core/math/rectangle.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, graphics, Texture);

namespace sani {

	namespace graphics {

		/*
			TODO: should be loaded from content?
		*/

		using SourceContainer = std::vector<math::Rect32f>;

		/// @class SpriteSheet sprite_sheet.hpp "sani/graphics/sprite_sheet.hpp"
		/// @author voidbab
		///
		/// Sheet that uses index based lookup for the sources.
		class SpriteSheet {
		public:
			Texture* const texture;
			SourceContainer sources;

			const uint32 sourceWidth;
			const uint32 sourceHeight;

			const uint32 rows;
			const uint32 columns;

			//// Creates new sprite sheet with given arguments.
			/// @param[in] texture texture that the sheet will be using
			/// @param[in] sourceWidth single sources width	
			/// @param[in] sourceHeight single sources height
			SpriteSheet(Texture* const texture, const uint32 sourceWidth, const uint32 sourceHeight);
			SpriteSheet();

			const math::Rect32f& sourceAt(const uint32 row, const uint32 column) const;

			~SpriteSheet() = default;
		};
	}
}