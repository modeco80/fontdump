//
// FontDump
//
// (C) 2021-2022 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include <font/RgbaImage.h>

namespace fd::font {

	RgbaImage::RgbaImage() = default;

	RgbaImage::RgbaImage(ImageSize size) {
		Resize(size);
	}

	void RgbaImage::Resize(ImageSize sz) {
		// Clear any remaining image.
		if(!pixels.empty())
			Clear();

		pixels.resize(sz.width * sz.height);
		size = sz;
	}

	void RgbaImage::Clear() {
		if(!pixels.empty()) {
			pixels.clear();
			size = { 0, 0 };
		}
	}

	const RgbaColor* RgbaImage::GetBuffer() const {
		if(pixels.empty())
			return nullptr;

		return pixels.data();
	}

	RgbaColor* RgbaImage::GetBuffer() {
		if(pixels.empty())
			return nullptr;

		return pixels.data();
	}

	std::size_t RgbaImage::GetStride() const {
		return 4 * size.width;
	}

	ImageSize RgbaImage::GetSize() const {
		return size;
	}

} // namespace fd::font