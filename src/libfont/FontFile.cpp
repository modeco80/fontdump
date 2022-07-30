//
// FontDump
//
// (C) 2021-2022 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include <font/FontFile.h>

#include <cstring>

#include "TrivialStreamRead.h"

namespace fd::font {

	ReadError File::ReadFromStream(std::istream& is) {
		if(!MaybeRead(is, header))
			return ReadError::FailureReadingHeader;

		// 1 column
		// std::uint32_t imwidth = header.originWidth;
		// std::uint32_t imheight = header.glyphCount * header.originHeight;

		// the size of the buffer that's given to the graphics library
		std::uint32_t imwidth = header.originWidth * 0x14;
		std::uint32_t imheight = (header.glyphCount / 0x14 + 1) * header.originHeight;

		// aligned to all the 0x0A chars
		// std::uint32_t imwidth = header.originWidth * 17;
		// std::uint32_t imheight = (header.glyphCount / 17 + 1) * header.originHeight;

		std::size_t imwidth_chars = imwidth / header.originWidth;
		std::size_t imheight_chars = imheight / header.originHeight;

		image.Resize({ imwidth, imheight });

		is.seekg(header.startOffset, std::istream::beg);

		for(auto i = 0; i < header.glyphCount; ++i) {
			// this is the original 4bpp image
			std::vector<uint8_t> imageTempBuffer(header.originWidth * header.originHeight / 2);
			GlyphHeader glyphHeader {};
			is.read(reinterpret_cast<char*>(&glyphHeader), sizeof(GlyphHeader));

			// std::printf("[%d] char 0x%03x, buf at 0x%06x\n", i, glyphHeader.sjisGlyph, is.tellg());

			is.read(reinterpret_cast<char*>(&imageTempBuffer[0]), imageTempBuffer.size());

			// this is conv'd to rgba and memcpy'd into the image. sucks but what can you do
			std::vector<RgbaColor> imageRgbaBuffer(header.originWidth * header.originHeight);

			// palette
			constexpr static RgbaColor pal[16] = {
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { .r = 0, .g = 0, .b = 0, .a = 255 },
				RgbaColor { 0xFFFFFFFF },
			};

			// Convert this glyph to an RGBA8888 image
			{
				auto* buffer = (imageRgbaBuffer.data());
				for(std::size_t j = 0; j < (header.originWidth * header.originHeight / 2); ++j)
					for(std::size_t b = 0; b < 2; b++)
						*(buffer++) = pal[static_cast<std::uint16_t>(((imageTempBuffer[j] & (0xF0 >> (b * 4))) >> ((1 - b) * 4)))];
			}

			// Write the RGBA glyph to the global font buffer.
			for(int y = 0; y < header.originHeight; ++y) {
				auto ypos = (((i * header.originWidth) / imwidth) * header.originHeight) + y;
				for(std::size_t x = 0; x < header.originWidth; ++x) {
					auto xpos = ((i * header.originWidth) % imwidth) + x;

					image.GetBuffer()[(imwidth * ypos) + xpos] = imageRgbaBuffer[(header.originWidth * y) + x];
				}
			}
		}

		return ReadError::NoError;
	}

	RgbaImage& File::GetImage() {
		return image;
	}

	const Header& File::GetHeader() const {
		return header;
	}
} // namespace fd::font