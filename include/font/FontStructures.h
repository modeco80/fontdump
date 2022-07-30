//
// TIPDump2
//
// (C) 2021-2022 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef TIPDUMP_TIP_STRUCTURES_H
#define TIPDUMP_TIP_STRUCTURES_H

#include <cstdint>

// All structures here are little endian...

namespace fd::font {

	struct Header {
		constexpr static auto VALID_MAGIC = 0x2303290; // todo valid magic soon

		std::uint32_t magic;
		std::uint32_t fileSize;

		std::uint16_t glyphCount;

		std::uint8_t startOffset; // ?

		// ?? treated as floats
		std::uint8_t fontSize;

		std::uint8_t originWidth;
		std::uint8_t originHeight;
	};

	struct GlyphHeader {
		std::uint16_t sjisGlyph;

		// Probably a kerning rect if I had to guess
		std::uint8_t xStart;
		std::uint8_t yStart;
		std::uint8_t width;
		std::uint8_t height;
	};

} // namespace fd::font
#endif // TIPDUMP_TIP_STRUCTURES_H